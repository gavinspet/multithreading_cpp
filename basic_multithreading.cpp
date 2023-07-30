#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void workfunction()
{
    for(int i=0;i<10;i++)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout<<"loop "<<i<<endl;
    }
}

int main()
{
    thread t1(workfunction);
    thread t2(workfunction);

    // cout<<"Hello world"<<endl;

    t1.join();
    t2.join();

    return 0; 
}