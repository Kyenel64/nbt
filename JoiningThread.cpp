#include "JoiningThread.h"

template<typename T, typename ... Args>
JoiningThread::JoiningThread(T&& func, Args&&... args)
{
    m_Thread = std::thread(std::forward<T>(func), std::forward<Args>(args)...);
}

JoiningThread::JoiningThread(std::thread t)
    : m_Thread(std::move(t))
{

}

JoiningThread::JoiningThread(JoiningThread&& other)
    : m_Thread(std::move(other.m_Thread))
{

}

JoiningThread& JoiningThread::operator=(JoiningThread&& other)
{
    if (Joinable())
        Join();
    m_Thread = std::move(other.m_Thread);
    return *this;
}

JoiningThread& JoiningThread::operator=(std::thread other)
{
    if (Joinable())
        Join();
    m_Thread = std::move(other);
    return *this;
}

JoiningThread::~JoiningThread()
{
    if (Joinable())
        Join();
}