// same as basics/09_...cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int counter = 0;

std::timed_mutex mtx;

void increment(int x)
{
    for(int i=0;i<x;i++)
    {   
        // it waits for sometime and then releases
        // can use mtx.try_lock_until too - use clock for that
        if(mtx.try_lock_for(std::chrono::milliseconds(100)));   
        {
        counter++;
        mtx.unlock();
        }
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