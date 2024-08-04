#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

std::mutex m1, m2;

void thread_f1()
{
    m1.lock();
    sleep(1);
    m2.lock();
    //////////////////////
    std::cout<<"critical section f1\n";
    /////////////////////
    m1.unlock();
    m2.unlock();
}

void thread_f2()
{
    m2.lock();
    sleep(1);
    m1.lock();
    //////////////////////
    std::cout<<"critical section f2\n";
    /////////////////////
    m2.unlock();
    m1.unlock();
}


int main()
{
    std::thread t1,t2;

    t1 = std::thread(thread_f1);
    t2 = std::thread(thread_f2);

    t1.join();
    t2.join();
}