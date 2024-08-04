#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void workfunction() {
  for (int i = 0; i < 10; i++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    mtx.lock(); // will pack call till unlock
    // this_thread::sleep_for(chrono::milliseconds(500));

    std::cout << "loop " << i << std::endl;

    std::thread::id currentThreadId = std::this_thread::get_id();
    std::cout << "Current thread ID: " << currentThreadId << std::endl;
    mtx.unlock();
  }
}

int main() {
  std::thread t1(workfunction);
  std::thread t2(workfunction);

  std::cout << "Hello world" << std::endl;

 

  t1.join();
  t2.join();

   std::thread s([]()
  {
    std::cout<<"meow\n";
  });

  s.join();

  return 0;
}