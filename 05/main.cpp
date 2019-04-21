#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex m;
std::condition_variable order;
bool pingord;

using uint = unsigned int;

constexpr uint num_of_pings = 500000;


void ping() // thread 1
{
    for(int i = 0; i < num_of_pings; ++i){

        std::unique_lock<std::mutex> lock(m);
        while (!pingord)
            order.wait(lock);
        std::cout << "ping\n";
        pingord = false;
        order.notify_one();
    }
    return;
}

void pong() // thread 2
{
    for(int i = 0; i < num_of_pings; ++i) {

        std::unique_lock<std::mutex> lock(m);
        while (pingord)
            order.wait(lock);
        std::cout << "pong\n";
        pingord = true;
        order.notify_one();
    }
    return;
}

int main()
{
    pingord = true;
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();

    return 0;
}