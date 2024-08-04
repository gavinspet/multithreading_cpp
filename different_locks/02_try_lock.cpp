// same as basics/09_...cpp

#include <iostream>
#include <thread>
#include <mutex>

int counter = 0;

std::mutex mtx;

void increment(int x)
{
    for(int i=0;i<x;i++)
    {
        // mutex is a blocking lock - it waits until it gets the lock
        // try lock is a non-blocking lock - it tries to lock and if can not get it
        // it skips the if condition
        if(mtx.try_lock())
        {
        counter++;
        mtx.unlock();
        }
    }

    // in this case since if condition will be skipped many times, so the answer won't be 2x
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