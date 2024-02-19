#include <iostream>
#include <thread>

#include "ThreadGuard.h"

void Hello(int val)
{
    std::cout << "Hello Concurrent program!" << " Val:" << val << "\n";
}

int main() // thread 1
{
    std::cout << std::thread::hardware_concurrency() << "\n";
    int localVal = 10;
    std::thread t1(Hello, localVal); // thread 2
    ThreadGuard tg1(t1);
    return 0;
}
