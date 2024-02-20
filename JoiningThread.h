#pragma once

#include <thread>

class JoiningThread
{
    public:
        JoiningThread() = default;
        template<typename T, typename ... Args>
        JoiningThread(T&& func, Args&&... args);
        JoiningThread(std::thread t);
        JoiningThread(JoiningThread&& other);
        ~JoiningThread();

        JoiningThread& operator=(JoiningThread&& other);
        JoiningThread& operator=(std::thread other);

        void Swap(JoiningThread& other) { m_Thread.swap(other.m_Thread); }
        void Join() { m_Thread.join(); }
        void Detach() { m_Thread.detach(); }

        bool Joinable() const { return m_Thread.joinable(); }
        std::thread::id GetID() const { return m_Thread.get_id(); }
        std::thread& GetThread() { return m_Thread; }
        const std::thread& GetThread() const { return m_Thread; }
    private:
        std::thread m_Thread;
};