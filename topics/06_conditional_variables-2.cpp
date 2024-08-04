#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool print_up = true; // flag to control the flow

const int n = 1000;

void print1ton()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return print_up; });

        for (int i = 1; i <= n; ++i)
        {
            std::cout << i << std::endl;
        }

        print_up = false;
        cv.notify_all();
    }
}

void printnto1()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !print_up; });

        for (int i = n; i >= 1; --i)
        {
            std::cout << i << std::endl;
        }

        print_up = true;
        cv.notify_all();
    }
}

int main()
{
    std::thread t1(print1ton);
    std::thread t2(printnto1);

    t1.join();
    t2.join();

    return 0;
}
