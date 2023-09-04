#include"log.h"
#include<thread>
#include<iostream>

// 获取唯一实列对象
Log& Log::getLogInstance()
{
    static Log log;
    return log;
}

Log::Log()
{
    // 启动专门的写日志线程
   std::thread wirteLogTask([&](){
        while(1)
        {
            // 获取当前日期，然后取日志信息，写入相应的日志文件当中 a+
            time_t now = time(nullptr);
            tm *nowtm = localtime(&now);

            char file_name[128];
            sprintf(file_name,"%d-%d-%d-log.txt",nowtm->tm_year+1900,nowtm->tm_mon+1,nowtm->tm_mday);

            FILE *pf = fopen(file_name,"a+");
            if(pf == nullptr)
            {
                std::cout<<"log file: "<<file_name<<"open error!"<<std::endl;
                exit(EXIT_FAILURE);
            }

            std::string msg = LogQueue.pop();
            fputs(msg.c_str(),pf);
            fclose(pf);
     
        }
    });
    
    // 设置分离线程，守护线程
    wirteLogTask.detach();
}

// 设置日志级别
void Log::setLogLevel(LogLevel level)
{
    m_logLevel = level;
}

// 写日志
void Log::setLog(std::string msg)
{
    LogQueue.push(msg);
}