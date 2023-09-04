#include"rpcApplication.h"
#include<iostream>
#include<unistd.h>

//静态变量在类内声明，在类外初始化
RpcConfig RpcApplication::m_config;

void showArgHelp()
{
    std::cout<<"format: command -i <configfile>"<<std::endl;
}


void RpcApplication::Init(int argc, char **argv)
{
    if(argc < 2)
    {
        showArgHelp();
        exit(EXIT_FAILURE);
    }

    int c = 0;
    std::string config_file;
    while((c = getopt(argc,argv,"i:")) != -1)
    {
        switch (c)
        {
        case 'i':
            config_file = optarg;            
            break;
        case '?':
            std::cout<<"invilid args!"<<std::endl;
            showArgHelp();
            exit(EXIT_FAILURE);
        case ':':
            std::cout<<"need <configfile>"<<std::endl;
            showArgHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件 rpcserverip rpcserverport zookeeperip zookeeperport
    m_config.LoadConfigFile(config_file.c_str());

    std::cout<<"rpcserverip:"<<m_config.Load("rpcserverip")<<std::endl;
    std::cout<<"rpcserverport:"<<m_config.Load("rpcserverport")<<std::endl;
    std::cout<<"zookeeperip:"<<m_config.Load("zookeeperip")<<std::endl;
    std::cout<<"zookeeperport:"<<m_config.Load("zookeeperport")<<std::endl;

}

RpcApplication& RpcApplication::GetInstance()
{
    static RpcApplication app;
    return app;
}

// 获取唯一配置的接口函数
RpcConfig & RpcApplication::GetConfig()
{
    return m_config;
}
