// Key Features
// Deferred Locking: You can construct a std::unique_lock without locking the mutex immediately.
// Timed Locking: You can attempt to acquire a lock for a specific duration or until a specific time point.
// Lock Ownership Transfer: You can transfer lock ownership between different std::unique_lock instances.
// Manual Locking and Unlocking: You can explicitly lock and unlock the mutex multiple times.

// deferred locking

#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void threadFunction(int id) {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Deferred locking

    // Do some work that does not require the lock
    std::cout << "Thread " << id << " doing some work before acquiring the lock.\n";

    // Now explicitly acquire the lock
    lock.lock();
    std::cout << "Thread " << id << " acquired the lock.\n";
    
    // Do work that requires the lock
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " releasing the lock.\n";
    
    // The lock will be automatically released when lock goes out of scope
}

int main() {
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);

    t1.join();
    t2.join();

    return 0;
}
