// Binary Semaphore
// A binary semaphore is a special case of a counting semaphore with a maximum count of 1. 
// It is typically used for signaling purposes.


#include <iostream>
#include <semaphore>
#include <thread>

std::binary_semaphore sem(0); // Binary semaphore with an initial count of 0

void worker(int id) {
    std::cout << "Worker " << id << " waiting for signal.\n";
    sem.acquire(); // Wait for a signal
    std::cout << "Worker " << id << " received signal.\n";
}

int main() {
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate some work

    std::cout << "Sending signal to workers.\n";
    sem.release(); // Signal one worker
    std::this_thread::sleep_for(std::chrono::seconds(1));
    sem.release(); // Signal the other worker

    t1.join();
    t2.join();

    return 0;
}
