
// A std::unique_lock in C++ is a flexible and 
// convenient locking mechanism provided by the C++ 
// Standard Library for managing mutexes. 
// It is part of the <mutex> header and 
// offers advanced locking capabilities compared to std::lock_guard

#include <iostream>
#include <mutex>
#include <thread>

int counter = 0;

std::mutex mtx;

void increment(int x)
{
    for(int i=0;i<x;i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        counter++;
        // mtx.unlock(); it automatically releases the lock once out of scope
        // but can unlock too
    }
}



int main()
{
    int x = 10000000;
    std::thread t1(increment,x);
    std::thread t2(increment,x);

    t1.join();
    t2.join();


    std::cout<<counter<<std::endl;
}