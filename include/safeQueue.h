#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H

#include<queue>
#include<string>
#include<mutex>
#include<condition_variable>


template<typename T>
class SafeQueue
{ 
public:
    SafeQueue(){}

    ~SafeQueue(){}
    // 入队
    void push(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        cv.notify_one();
    }

    // 出队
    T &pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        // 使用while避免虚假唤醒
        while (m_queue.empty())
        {
            // 日志队列为空，线程进入wait状态
            cv.wait(lock);
        }

        pop_data = m_queue.front();
        m_queue.pop();
        return pop_data;
    }

private:
    // 线程安全互斥锁
    std::mutex m_mutex;
    // 条件变量
    std::condition_variable cv;
    // 消息队列
    std::queue<T> m_queue;
    // pop_data
    T pop_data;
};
 

#endif