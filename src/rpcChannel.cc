#include"rpcChannel.h"
#include<string>
#include"rpcHeader.pb.h"
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include"rpcApplication.h" 
#include"zookeeperUtil.h"
#include"log.h"

// 所有通过stub代理对象调用rpc方法，最终都是通过这个接口函数统一做数据的序列化和网络发送
void MyRpcChannel::CallMethod(const google::protobuf::MethodDescriptor *method,
                google::protobuf::RpcController *controller,
                const google::protobuf::Message *request,
                google::protobuf::Message *response,
                google::protobuf::Closure *done)
{
    const google::protobuf::ServiceDescriptor *sd = method->service();
    std::string service_name = sd->name();
    std::string method_name = method->name();    


    //获取参数的序列化字符串长度 args_size
    std::string args_str;
    int args_size = 0;
    if(request->SerializeToString(&args_str))
    {
        args_size = args_str.size();
    }
    else
    {
        std::cout<<"serialize request error!"<<std::endl;
        controller->SetFailed("serialize request error!");
        LOG_ERROR("serialize request error!");
        return ;
    }

    //定义rpc的请求header
    rpc::RpcHeader header;
    header.set_service_name(service_name);
    header.set_method_name(method_name);
    header.set_args_size(args_size);

    uint32_t header_size = 0;
    std::string header_str;
    if(header.SerializeToString(&header_str))
    {
        header_size = header_str.size();
    }
    else
    {
        std::cout<<"serialize request error!"<<std::endl;
        controller->SetFailed("serialize request error!");
        LOG_ERROR("serialize request error!");
        return ; 
    }

    // 组织待发送的rpc请求的字符串
    std::string send_header_str; 

    send_header_str.insert(0,std::string((char*)&header_size,4));
    send_header_str += header_str;
    send_header_str += args_str;     

    //std::cout<<"send_header_str: "<<send_header_str<<std::endl;

    // 打印调试信息
    std::cout << "=========================" << std::endl;
    std::cout << "header_size: " << header_size << std::endl;
    std::cout << "rpc_header_str: " << header_str << std::endl;
    std::cout << "service_name: " << service_name << std::endl;
    std::cout << "method_name: " << method_name << std::endl;
    std::cout << "args_str: " << args_str << std::endl;
    std::cout << "=========================" << std::endl;

    //使用tcp编程，完成rpc方法的远程调用
    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == clientfd)
    {
        std::cout<<"create socket error!"<<std::endl;
        controller->SetFailed("create socket error!");
        LOG_ERROR("create socket error!");
        return;
    }

    //读取配置文件rpcserver的信息    
    // std::string ip = RpcApplication::GetInstance().GetConfig().Load("rpcserverip");
    // uint16_t port = atoi(RpcApplication::GetInstance().GetConfig().Load("rpcserverport").c_str());

    ZkClient zkclient;
    zkclient.start();
    std::string method_path = "/" + service_name + "/" + method_name;
    std::string host_data = zkclient.getData(method_path.c_str());

    if(host_data == "")
    {
        controller->SetFailed(method_path + "is not exist!");
        LOG_ERROR("%s is not exit!",method_path);
        return;
    }
    int idx = host_data.find(":");
    if(idx == -1)
    {
        controller->SetFailed(method_path + "address is invilid");
        LOG_ERROR("%s address is invilid",method_path);
        return;
    }

    std::string ip = host_data.substr(0,idx);
    uint16_t port = atoi(host_data.substr(idx+1,host_data.size()-idx).c_str());

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
     
    // 连接rpc服务节点
    if(-1 == connect(clientfd,(struct sockaddr*)&server_addr,sizeof(server_addr)))
    { 
        // 连接失败
        std::cout<<"connect error! errno: "<<errno<<std::endl;
        LOG_ERROR("connect error! errno: %d",errno);
        std::string false_msg = "connect error! errno: ";
        false_msg += errno;
        controller->SetFailed(false_msg);
        close(clientfd);
        exit(EXIT_FAILURE);
    }
    
    int send_res = 0;
    // 发送rpc请求
   // if(-1 == (send_res = send(clientfd,&send_header_str,sizeof(send_header_str),0))) sizeof运算符计算的是类型大小
   if(-1 == (send_res = send(clientfd,send_header_str.c_str(),send_header_str.size(),0)))
    {
        std::cout<<"send error! errno: "<<errno<<std::endl;    
        LOG_ERROR("connect error! errno: %d",errno); 
        std::string false_msg = "send error! errno: ";
        false_msg += errno;
        controller->SetFailed(false_msg);     
        return;
    }    

    // 接受rpc请求
    char recv_buf[1024] = {0};
    int recv_size = 0;
    if(-1 == (recv_size = recv(clientfd,&recv_buf,1024,0)))
    {
        std::cout<<"recv error! errno: "<<errno<<std::endl;
        LOG_ERROR("recv error! errno: %d",errno);
        std::string false_msg = "recv error! errno: ";
        false_msg += errno;
        controller->SetFailed(false_msg);
        close(clientfd);
        return;
    }
    

    // 反序列化
    //std::string response_str(recv_buf,0,recv_size);
    //if(!response->ParseFromString(recv_buf)) 含有bug
    if(!response->ParseFromArray(recv_buf,recv_size))
    {
        std::cout<<"parse error! response_str!"<<std::endl;
        LOG_ERROR("parse error! response_str!");
        controller->SetFailed("parse error! response_str!");
        close(clientfd);
        return;
    }

    //std::cout<<"recv_buf parse "<<recv_buf<<std::endl;
    close(clientfd);

}
