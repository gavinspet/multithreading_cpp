#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

int static var = 0;
std::queue<int> blocking_queue;
std::mutex mtx;

void read_queue() {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    if (!blocking_queue.empty()) {
      std::cout << "element read = " << blocking_queue.front() << std::endl;
      blocking_queue.pop();
    }
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

int main() {
  std::thread read_thread(read_queue);

  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    blocking_queue.push(++var);
    std::cout << "element write = " << var << std::endl;
    lock.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  read_thread.join();
  return 0;
}
