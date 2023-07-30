#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

int main()
{
    int count = 0;
    const int INCREMENT = 10000000;

    thread t1([&count](){

        for(int i = 0; i < INCREMENT; i++)
        {
            count++;
        }
    });

     thread t2([&count](){

        for(int i = 0; i < INCREMENT; i++)
        {
            count++;
        }
    });

    t1.join();
    t2.join();

    cout<<count<<endl;
}