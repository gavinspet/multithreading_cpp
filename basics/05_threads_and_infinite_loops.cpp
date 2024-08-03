#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <unistd.h>

std::atomic<int> count(0);
std::mutex mtx;

void func()
{
  count++;
  // mtx.lock();
  while(1)
  {
  std::cout << std::this_thread::get_id() << std::endl;
  sleep(1);
  }
  // mtx.unlock();
}

int main()
{

  std::thread t[20];
  
  for(int i=0;i<20;i++)
  t[i] = std::thread(func);
  
  for(int i=0;i<20;i++)
  t[i].join();

  return 0;
}
