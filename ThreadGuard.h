#pragma once

#include <thread>

class ThreadGuard
{
    public:
        ThreadGuard(std::thread& t);
        ~ThreadGuard();

        // Disable copy constructor and copy assignment
        ThreadGuard(ThreadGuard const&) = delete;
        ThreadGuard& operator=(ThreadGuard const&) = delete;
    private:
        std::thread& m_Thread;
};