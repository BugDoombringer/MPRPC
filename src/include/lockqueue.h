#pragma once
#include <queue>
#include <thread>
#include <mutex> 
#include <condition_variable>

// 异步写日志的日志队列
template<typename T>
class LockQueue
{
public:
    // 多个worker线程都会写日志queue 
    void Push(const T &data)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(data);
        m_condvariable.notify_one();
    }

    // 一个线程读日志queue，写日志文件
    /*
        当前线程先获得 m_mutex 锁，进入临界区。
        调用 m_condvariable.wait(lock) 使线程等待，并暂时释放锁 m_mutex，以便其他线程可以获得锁并修改状态。
        当另一个线程通过 notify_one() 或 notify_all() 通知该条件变量时，当前线程被唤醒。
        线程醒来后，wait 会自动重新获取锁 m_mutex，然后继续执行后续代码。
    */
    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            // 日志队列为空，线程进入wait状态
            m_condvariable.wait(lock);
        }

        T data = m_queue.front();
        m_queue.pop();
        return data;
    }
private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condvariable;
};