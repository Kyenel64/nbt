#include "ThreadGuard.h"

ThreadGuard::ThreadGuard(std::thread& t)
    : m_Thread(t)
{

}

ThreadGuard::~ThreadGuard()
{
    if (m_Thread.joinable())
        m_Thread.join();
}