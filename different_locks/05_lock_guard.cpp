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
        // lock guard is light weight wrapper class of mutex
        // it acquires the lock every time it makes the object
        // when the object gets out of scope, the lock releases
        // there is no mechanism to unlock it
        // lock cannot be moved as well
        std::lock_guard<std::mutex> m(mtx);
        counter++;
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