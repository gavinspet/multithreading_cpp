#include<iostream>
#include<thread>
#include<chrono>
#include <mutex>

using namespace std;

mutex mtx;

void workfunction()
{
    for(int i=0;i<10;i++)
    {
        this_thread::sleep_for(chrono::milliseconds(500));

        mtx.lock();
        // this_thread::sleep_for(chrono::milliseconds(500));

        cout<<"loop "<<i<<endl;

        std::thread::id currentThreadId = std::this_thread::get_id();
        std::cout << "Current thread ID: " << currentThreadId << std::endl;
        mtx.unlock();
    }
}

int main()
{
    thread t1(workfunction);
    thread t2(workfunction);

    cout<<"Hello world"<<endl;

    t1.join();
    t2.join();

    return 0; 
}