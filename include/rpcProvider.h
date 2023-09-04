# ifndef RPCPROVIDER_H
# define PRCPROVIDER_H

#include"google/protobuf/service.h"
#include"muduo/net/TcpServer.h"
#include"muduo/net/EventLoop.h"
#include"muduo/net/InetAddress.h"
#include<memory>
#include"rpcApplication.h"
#include<unordered_map>
#include<functional>
#include<google/protobuf/descriptor.h>
#include"rpcHeader.pb.h"

class RpcProvider
{
public:
    // 提供发布rpc方法的函数接口
    void NotifyService(google::protobuf::Service * service);

    // 启动rpc服务节点，开始提供rpc远程调用服务
    void Run();

private:
    // 组合TcpServer
    std::unique_ptr<muduo::net::TcpServer>m_tcpserverPtr;

    // 组合EventLoop
    muduo::net::EventLoop  m_eventLoop;

    //服务类型信息
    struct ServiceInfo
    {
        //保存服务对象
        google::protobuf::Service *m_service;
        //保存服务方法
        std::unordered_map<std::string,const google::protobuf::MethodDescriptor*>m_methodMap;
    };

    //存储注册成功的服务对象和其服务方法的所有信息
    std::unordered_map<std::string,ServiceInfo>m_servicMap;


    // 连接回调函数
    void OnConnection(const muduo::net::TcpConnectionPtr&);

    // 消息读写回调函数
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*,muduo::Timestamp);

    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&,google::protobuf::Message*);
};


#endif