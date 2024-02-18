#include <iostream>
#include <thread>

void Hello()
{
    std::cout << "Hello Concurrent program!\n";
}

int main() // thread 1
{
    std::thread t1(Hello); // thread 2
    t1.join();
    return 0;
}
