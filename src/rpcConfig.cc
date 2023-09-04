#include"rpcConfig.h"
#include"log.h"
#include<iostream>
// 负责解析加载配置文件
void RpcConfig::LoadConfigFile(const char *config_file)
{
    FILE *pf = fopen(config_file,"r");
    if(nullptr == pf)
    {
        std::cout<<config_file<<" is not exist!"<<std::endl;
        LOG_ERROR("%s is not exist!",config_file);
        exit(EXIT_FAILURE);
    }
    // else
    // {
    //     std::cout<<"config_file open"<<std::endl;
    // }

    //1.去除注释 2.读取正确配置项 3.去掉开头多余空格
    while(!feof(pf))
    {
        char buf[512];
        fgets(buf,512,pf);

        //去掉字符串前多余空格
        std::string read_buf(buf);
        Tirm(read_buf);

        // 判断#的注释
        if(read_buf[0] == '#'|| read_buf.empty())
        {            
            continue;
        }

        // 解析配置项
        int idx = read_buf.find_first_of('=');
        if(idx == -1)
        {             
            //缺少=,说明配置项不合理
            continue;
        }
        else
        {
            std::string key;
            std::string value;

            // 解析出配置属性项key，并去除多余的空格
            key = read_buf.substr(0, idx);
            Tirm(key);//自定义的去除多余空格函数

            // 解析出属性项对应的值value,并去除多余的空格
            int endidx = read_buf.find('\n',idx);
            value = read_buf.substr(idx + 1, endidx - idx - 1);
            //防止换行符前有多余的空格
            Tirm(value);

            m_configMap.insert({key, value});

            // std::cout<<key<<value<<std::endl;
            // std::cout<<"------"<<std::endl;
        }
    }

}

// 查询配置项信息
std::string RpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if(it == m_configMap.end())
    {
        return "未找到";
    }
    return it->second;
}

// 去掉开头和结尾的空格
void RpcConfig::Tirm(std::string &src_buf)
{
    int idx = src_buf.find_first_not_of(' ');
    if (idx != -1)
    {
        // 说明字符串前有空格
        src_buf = src_buf.substr(idx, src_buf.size() - idx);
    }

    // 去掉字符串后面多余空格
    idx = src_buf.find_last_not_of(' ');
    if (idx != -1)
    {
        src_buf = src_buf.substr(0, idx + 1);
    }
}
