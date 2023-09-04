#ifndef RPCCONFIG_H
#define RPCCONFIG_H

#include<unordered_map>
#include<string>

//框架读取配置文件
//rpcserverip rpcserverport zookeeperip zookeeperport
class RpcConfig
{
public:
    //负责解析加载配置文件
    void LoadConfigFile(const char *config_file);

    //查询配置项信息
    std::string Load(const std::string &key);

    // 去掉开头和结尾的空格
    void Tirm(std::string & src_buf); 


private:
    //配置项映射表
    std::unordered_map<std::string,std::string>m_configMap;
};

# endif