#include <iostream>
#include <thread>
#include <mutex>

std::recursive_mutex rec_mtx;

void recursiveFunction(int count) {
    if (count <= 0) {
        return;
    }

    rec_mtx.lock();
    std::cout << "Lock acquired, count: " << count << std::endl;

    // Call the function recursively
    recursiveFunction(count - 1);

    std::cout << "Unlocking, count: " << count << std::endl;
    rec_mtx.unlock();
}

int main() {
    std::thread t1(recursiveFunction, 3);
    t1.join();

    return 0;
}
