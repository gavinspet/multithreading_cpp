#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void work(int &count, mutex &mtx) {
  for (int i = 0; i < 1E6; i++) {
    lock_guard<mutex> guard(mtx);
    // mtx.lock();
    count++;
    // mtx.unlock();
  }
}

int main() {
  int count = 0;

  mutex mtx;

  thread t1(work, ref(count), ref(mtx));
  thread t2(work, ref(count), ref(mtx));

  t1.join();
  t2.join();

  std::cout << count << endl;
}