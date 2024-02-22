#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#include "ThreadGuard.h"

// Put mutex along side data. In class, make both member variables.
std::vector<int> SomeVector;
std::mutex SomeMutex;

void Hello(int val)
{
    std::cout << "Hello Concurrent program!" << " Val:" << val << "\n";
}

void AddToVector(int value)
{
    std::scoped_lock guard(SomeMutex);
    SomeVector.push_back(value);
}

bool Contains(int value)
{
    std::scoped_lock guard(SomeMutex);
    return std::find(SomeVector.begin(), SomeVector.end(), value) != SomeVector.end();
}

int main() // thread 1
{
    int maxThreads = std::thread::hardware_concurrency();
    int localVal = 10;
    std::thread t1(Hello, localVal); // thread 2. localVal is a pointer to the local val. 
    ThreadGuard tg1(t1);

    int maxNumberOfPrints = 5;
    // Dont create max num of threads if unneeded
    maxThreads > maxNumberOfPrints ? maxThreads = maxNumberOfPrints : maxThreads;
    std::vector<std::thread> threads;
    for (int i = 0; i < maxThreads-1; i++)
    {
        threads.emplace_back(Hello, 10);
    }
    for (auto& thread : threads)
    {
        std::cout << "Joining thread ID: " << thread.get_id() << "\n";
        thread.join();
    }
    return 0;
}
