#include"rpcProvider.h"
#include"zookeeperUtil.h"
#include"log.h"
#include"muduo/base/LogFile.h"

// 提供发布rpc方法的函数接口
void RpcProvider::NotifyService(google::protobuf::Service *service)
{ 
    // 一个服务对象有多个服务方法      
    ServiceInfo service_info;

    // 获取了服务对象的描述信息
    const google::protobuf::ServiceDescriptor* serviceDesc = service->GetDescriptor();
    // 获取服务的名字
    std::string service_name = serviceDesc->name();
    // 获取服务对象service的方法数量
    int methodCnt = serviceDesc->method_count();

    std::cout<<"service_name:"<<service_name<<std::endl;
    std::string loginfo = "service_name:" + service_name;
    LOG_INFO(loginfo.c_str());

    for(int i = 0; i < methodCnt; ++i)
    {
        // 获取了服务对象指定下标的服务方法的描述(抽象描述)
        const google::protobuf::MethodDescriptor* methodDesc = serviceDesc->method(i);
        std::string method_name = methodDesc->name();
        service_info.m_methodMap.insert({method_name,methodDesc});

        std::cout<<"service_method:"<<method_name<<std::endl;
        std::string loginfo = "service_method:" + method_name;
        LOG_INFO(loginfo.c_str());
    }

    service_info.m_service = service;
    m_servicMap.insert({service_name,service_info});

}

// 启动rpc服务节点，开始提供rpc远程调用服务
void RpcProvider::Run()
{
    std::string ip = RpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    uint16_t port = atoi(RpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

    muduo::net::InetAddress address(ip,port);

    //创建TcpServer对象
    muduo::net::TcpServer server(&m_eventLoop,address,"RpcServer");

    // 使用muduo网络库分离了网络代码与业务代码
    //绑定连接回调方法
    server.setConnectionCallback(std::bind(&RpcProvider::OnConnection,this,std::placeholders::_1));
    //绑定消息读写回调方法
    server.setMessageCallback(std::bind(&RpcProvider::OnMessage,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));

    // 设置muduo库线程数量
    server.setThreadNum(4);

    //把当前rpc节点生要发布的服务全部注册到zookeeper上，让rpc client可以在zookeeper上发现服务
    ZkClient zkclient;
    zkclient.start();

    //service_name为永久性节点  method_name为临时性节点
    for(auto &sp : m_servicMap)
    {
        std::string service_path = "/" + sp.first;
        zkclient.create(service_path.c_str(),nullptr,0);
        for(auto &mp :sp.second.m_methodMap)
        {
            // 存储当前这个rpc服务节点主机的ip和port
            std::string method_path = service_path + "/" +mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data,"%s:%d",ip.c_str(),port);
            // ZOO_EPHEMERAL 表示一个临时节点
            zkclient.create(method_path.c_str(),method_path_data,strlen(method_path_data),ZOO_EPHEMERAL);
        }
        
    }



    std::cout<<"RpcProvider start server at ip:"<<ip<<" port:"<<port<<std::endl;
    std::string loginfo = "RpcProvider start server at ip::" + ip + " port:";
    loginfo.append(std::to_string(port));     
    LOG_INFO(loginfo.c_str());

    // 启动网络服务
    server.start();
    m_eventLoop.loop();

}

// 连接回调函数
void RpcProvider::OnConnection(const muduo::net::TcpConnectionPtr & conn)
{
    //和rpc client的连接断开了
    if(!conn->connected())
    {
        conn->shutdown();
    }
}

// 消息读写回调函数
void RpcProvider::OnMessage(const muduo::net::TcpConnectionPtr & conn, muduo::net::Buffer * buff, muduo::Timestamp time)
{
    // 网络上接受远程rpc调用请求的字符流
    std::string recv_buf = buff->retrieveAllAsString();

    // if(!recv_buf.empty())
    // {
    //     std::cout<<"not empty"<<std::endl;
    //     std::cout<<"recv_buf: "<<recv_buf<<std::endl;
    // }


    //自定义框架内部RpcProvider和RpcConsumer之间通信用的protobuf数据类型
    //采用header_size(4字节)+header_str+args_str 解决粘包问题

    //从字符流中读取前4个字节的内容
    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size,4,0);
 

    // 根据header_size读取数据头的原始字符流，反序列化数据，得到rpc请求的详细信息
    std::string rpc_header_str = recv_buf.substr(4,header_size);
    rpc::RpcHeader rpcHeader;
    std::string service_name;
    std::string method_name;
    uint32_t args_size;    


    if(rpcHeader.ParseFromString(rpc_header_str))
    {
        //数据头反序列化成功
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    }
    else
    {
        //数据头反序列化失败
        std::cout<<"rpc_header_str: "<<rpc_header_str<<" parse error!"<<std::endl;
        std::string logerror = "rpc_header_str: "+ rpc_header_str + " parse error!";
        LOG_ERROR(logerror.c_str());
        return ;
    }

    // 获取rpc方法参数的字符流数据
    std::string args_str = recv_buf.substr(4+header_size,args_size);

    // 打印调试信息
    std::cout<<"========================="<<std::endl;
    std::cout<<"header_size: "<<header_size<<std::endl;
    std::cout<<"rpc_header_str: "<<rpc_header_str<<std::endl;
    std::cout<<"service_name: "<<service_name<<std::endl;
    std::cout<<"method_name: "<<method_name<<std::endl;
    std::cout<<"args_str: "<<args_str<<std::endl;
    std::cout<<"========================="<<std::endl;

    //获取service对象和method对象
    auto it = m_servicMap.find(service_name);
    if(it == m_servicMap.end())
    {
        std::cout<<service_name<<" is not exit!"<<std::endl;
        LOG_ERROR("%s is not exit!",service_name);
        return;
    }

    auto mit = it->second.m_methodMap.find(method_name);
    if(mit == it->second.m_methodMap.end())
    {
        std::cout<<service_name<<":"<<method_name<<"is not exit!"<<std::endl;
        LOG_ERROR("%s:%s is not exit!",service_name,method_name);
        return;
    }

    // 获取service对象
    google::protobuf::Service* service = it->second.m_service;
    //获取method对象
    const google::protobuf::MethodDescriptor* method = mit->second;

    //生成rpc方法调用的request和response参数
    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str))
    {
        std::cout<<"request parse error,content:"<<args_str<<std::endl;
        LOG_ERROR("request parse error,content:%s",args_str);
        return;
    }
    google::protobuf::Message* response = service->GetResponsePrototype(method).New();

    //给method方法调用绑定一个Closure的回调函数
    google::protobuf::Closure* done = google::protobuf::NewCallback<RpcProvider,
                                                                    const muduo::net::TcpConnectionPtr&,
                                                                    google::protobuf::Message*>(this,&RpcProvider::SendRpcResponse,conn,response);

    //在框架上根据远端rpc请求，调用当前rpc节点上发布的方法
    service->CallMethod(method,nullptr,request,response,done);


}

// Closure的回调操作，用于序列化rpc的响应和网络发送
void RpcProvider::SendRpcResponse(const muduo::net::TcpConnectionPtr& conn,google::protobuf::Message* response)
{
    std::string response_str;
    if(response->SerializeToString(&response_str))
    {
        //序列化成功后，通过网络把rpc方法执行结果发送给rpc的调用方
        conn->send(response_str);
    }
    else
    {
        std::cout<<"Serialize respnse_str error!"<<std::endl;
        LOG_ERROR("Serialize respnse_str error!");
    }
    //模拟http短连接，由rpcprovider主动断开连接
    conn->shutdown();
} 

