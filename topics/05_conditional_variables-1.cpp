#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool flag = true;

int i = 0; // shared resource
int n = 10;

void print1ton()
{
     while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return flag; });

        for (i = 1; i <= n; ++i)
        {
            std::cout << i << std::endl;
        }

        flag = false;
        cv.notify_one();
    }
}


void printnto1()
{
     while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !flag; });

        for (i = n; i >= 1; --i)
        {
            std::cout << i << std::endl;
        }

        flag = true;
        cv.notify_one();
    }
}


int main()
{
    std::thread t1(print1ton);
    std::thread t2(printnto1);

    t1.join();
    t2.join();
}