#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int main() {
  int count = 0;
  const int INCREMENT = 10000000;

  mutex mtx;

  auto funct = [&]() {
    for (int i = 0; i < INCREMENT; i++) {
      mtx.lock();
      count++;
      mtx.unlock();
    }
  };

  thread t1(funct);
  thread t2(funct);

  t1.join();
  t2.join();

  std::cout << count << endl;
}