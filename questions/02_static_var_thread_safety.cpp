// same as basics/09_...cpp

#include <iostream>
#include <thread>
#include <mutex>

static int counter = 0;

std::mutex mtx;

/* Solving the race condition using lock */
/* another way would be to use atomic variable - already mastered it*/

void increment(int x)
{
    for(int i=0;i<x;i++)
    {
        // shared resource - race condition between multiple threads
        // mtx.lock();
        counter++;
        // mtx.unlock();
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