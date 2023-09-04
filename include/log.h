#ifndef LOG_H
#define LOG_H

#include"safeQueue.h"

// 日志信息类型
enum LogLevel
{
    INFO,//普通信息类型
    ERROR,//错误信息类型
};

//单例模式设计日志
class Log
{   
public:
    //获取唯一实列对象
    static Log& getLogInstance();
    //设置日志级别
    void setLogLevel(LogLevel level);
    //写日志
    void setLog(std::string msg);
   
private:
    // 日志队列
    SafeQueue<std::string> LogQueue;
    // 日志级别类型
    LogLevel m_logLevel; 
    Log();
    //禁用拷贝构造
    Log(const Log&) = delete;
    Log(Log&&) = delete;
};

// 定义宏 LOG_INFO("xxx %d %s",20,"XXXX")
#define LOG_INFO(logmsgformat, ...) \
    do \
    {  \
        Log &log = Log::getLogInstance(); \
        log.setLogLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c,1024,logmsgformat, ##__VA_ARGS__); \
        std::string midinfo(c); \
        midinfo.append("\n"); \
        log.setLog(midinfo); \
    }while(0)

// 定义宏 LOG_ERROR("xxx %d %s",20,"XXXX")
#define LOG_ERROR(logmsgformat, ...) \
    do \
    {  \
        Log &log = Log::getLogInstance(); \
        log.setLogLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c,1024,logmsgformat, ##__VA_ARGS__); \
        std::string midinfo(c); \
        midinfo.append("\n"); \
        log.setLog(c); \
    }while(0)

#endif
