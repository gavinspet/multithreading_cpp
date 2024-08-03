#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <unistd.h>

#define number_of_thread 100
#define iterations 1000000000000

std::atomic<int> count(0);
std::mutex mtx;

void func()
{
  count++;
  mtx.lock();
  for (int i = 0; i < iterations; ++i)
  {
    std::cout << count << " : " << std::this_thread::get_id() << std::endl;
    // sleep(1);
  }
  mtx.unlock();
}

int main()
{
  std::cout << "Number of hardware threads: "
            << std::thread::hardware_concurrency() << std::endl;

  std::thread t[number_of_thread];
  
  for (int i = 0; i < number_of_thread; ++i)
    t[i] = std::thread(func);
  
  for (int i = 0; i < number_of_thread; ++i)
    t[i].join();

  return 0;
}
