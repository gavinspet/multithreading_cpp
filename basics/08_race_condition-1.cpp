#include <iostream>
#include <thread>

int counter = 0;


void increment(int x)
{
    for(int i=0;i<x;i++)
    {
        // shared resource - race condition between multiple threads
        counter++;
    }
}

/*
  The increment function increments the global counter 10000 times. 
  However, because counter is shared between t1 and t2, the final 
  value of counter may not be 20000. This is because the counter++ 
  operation is not atomic; it consists of multiple steps:

Read the value of counter.
Increment the value.
Write the new value back to counter.
When two threads execute counter++ simultaneously, 
the operations can interleave in such a way that both threads 
read the same value of counter, increment it, and write it back, 
resulting in only one increment instead of two.
*/


int main()
{
    int x = 10000;
    std::thread t1(increment,x);
    std::thread t2(increment,x);

    t1.join();
    t2.join();


    std::cout<<counter<<std::endl;
}