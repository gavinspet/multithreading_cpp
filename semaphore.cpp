#include <bits/stdc++.h>
#include <future>
#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>

std::semaphore semaphore(2); // Initialize a semaphore with a count of 2

void worker(int id) {
  std::cout << "Thread " << id << " is trying to access the shared resource."
            << std::endl;

  semaphore.acquire(); // Decrease the semaphore count by 1
  std::cout
      << "Thread " << id
      << " has acquired the semaphore and is accessing the shared resource."
      << std::endl;

  // Simulate some work
  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "Thread " << id
            << " is releasing the semaphore and leaving the shared resource."
            << std::endl;
  semaphore.release(); // Increase the semaphore count by 1
}

int main() {
  const int numThreads = 5;
  std::thread threads[numThreads];

  for (int i = 0; i < numThreads; ++i) {
    threads[i] = std::thread(worker, i);
  }

  for (int i = 0; i < numThreads; ++i) {
    threads[i].join();
  }

  return 0;
}
