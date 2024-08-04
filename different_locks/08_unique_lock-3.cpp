// adopt locking
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void threadFunction(int id) {
    mtx.lock(); // Lock the mutex manually
    std::cout << "Thread " << id << " manually locked the mutex.\n";

    std::unique_lock<std::mutex> lock(mtx, std::adopt_lock); // Adopt the already locked mutex
    std::cout << "Thread " << id << " is now managing the lock with std::unique_lock.\n";

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
