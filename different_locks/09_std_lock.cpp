// std::lock is a utility function in C++ that is used to lock 
// multiple mutexes at once without causing deadlock. 
// It ensures that all mutexes passed to it are locked in a deadlock-free manner.


#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1, mtx2;

void threadFunction1() {
    std::lock(mtx1, mtx2); // Lock both mutexes

    // Use std::lock_guard or std::unique_lock to manage the locked mutexes
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);

    std::cout << "Thread 1 has locked both mtx1 and mtx2\n";

    // Critical section
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void threadFunction2() {
    std::lock(mtx1, mtx2); // Lock both mutexes

    // Use std::lock_guard or std::unique_lock to manage the locked mutexes
    std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);

    std::cout << "Thread 2 has locked both mtx1 and mtx2\n";

    // Critical section
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    std::thread t1(threadFunction1);
    std::thread t2(threadFunction2);

    t1.join();
    t2.join();

    return 0;
}



/*
Key Points
Avoiding Deadlock: std::lock ensures that the mutexes are locked in a way that avoids deadlock.
Adopt Lock: After calling std::lock, you should use std::lock_guard or std::unique_lock 
with std::adopt_lock to manage the mutexes, indicating that the mutexes are already locked.
Flexibility: std::lock can handle any number of mutexes, making it flexible for complex scenarios.
*/

