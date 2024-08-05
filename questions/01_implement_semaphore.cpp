// step -1 : understand semaphore well

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count = 0)
        : count(count) {}

    // Acquire the semaphore (decrement the count)
    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]() { return count > 0; });
        --count;
    }

    // Release the semaphore (increment the count)
    void release() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

void task(Semaphore& sem, int id) {
    std::cout << "Thread " << id << " is waiting to acquire the semaphore\n";
    sem.acquire();
    std::cout << "Thread " << id << " has acquired the semaphore and entered the critical section\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread " << id << " is leaving the critical section and releasing the semaphore\n";
    sem.release();
}

int main() {
    Semaphore sem(1); // Binary semaphore initialized with count 1
    std::thread t1(task, std::ref(sem), 1);
    std::thread t2(task, std::ref(sem), 2);

    t1.join();
    t2.join();

    return 0;
}
