#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

void work(int &count, mutex &mtx) {
  while (true) {
    this_thread::sleep_for(chrono::milliseconds(500));
    mtx.lock();
    // for(int i = 0; i < 1E6; i++)
    // {
    //     count++;
    //     // exception ..........
    // }
    std::thread::id currentThreadId = std::this_thread::get_id();
    std::cout << "Current thread ID: " << currentThreadId << std::endl;
    cout << "\nRUNNING\n";

    mtx.unlock();
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