# ifndef RPCAPPLICATION_HPP
# define RPCAPPLICATION_HPP

#include"rpcConfig.h"
#include"rpcController.h"


// rpc框架的基础类
// 设计未单例模式，共享配置文件、日志文件等信息
class RpcApplication
{
public:
    // 配置rpc节点的ip+port
    static void Init(int argc,char **argv);

    // 获取唯一实例对象的接口函数
    static RpcApplication& GetInstance();
    
    // 获取唯一配置的接口函数
    static RpcConfig& GetConfig();

private:
    RpcApplication(){}
    
    // 禁用拷贝构造函数
    RpcApplication(const RpcApplication&) = delete;
    RpcApplication(RpcApplication&&) = delete; 

    //读取配置文件
    static RpcConfig m_config;
};
# endif