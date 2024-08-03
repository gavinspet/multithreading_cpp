#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> buffer;

const int BUFFER_SIZE = 5;

void producer() {
  for (int i = 1; i <= 10; ++i) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(500)); // Simulate some work
    std::unique_lock<std::mutex> lock(mtx);

    while (buffer.size() >= BUFFER_SIZE) {
      cv.wait(lock); // Wait for the consumer to consume
    }

    buffer.push(i);
    std::cout << "Produced: " << i << std::endl;

    lock.unlock();
    cv.notify_all(); // Notify the consumer
  }
}

void consumer() {
  for (int i = 1; i <= 10; ++i) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(700)); // Simulate some work
    std::unique_lock<std::mutex> lock(mtx);

    while (buffer.empty()) {
      cv.wait(lock); // Wait for the producer to produce
    }

    int value = buffer.front();
    buffer.pop();
    std::cout << "Consumed: " << value << std::endl;

    lock.unlock();
    cv.notify_all(); // Notify the producer
  }
}

int main() {
  std::thread producer_thread(producer);
  std::thread consumer_thread(consumer);

  producer_thread.join();
  consumer_thread.join();

  return 0;
}
