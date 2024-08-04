// Counting Semaphore
// A counting semaphore has a count that can be incremented or decremented. 
// It can be used to manage access to a pool of resources.

#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

std::counting_semaphore<3> sem(3); // Semaphore with an initial count of 3

void worker(int id) {
    sem.acquire(); // Acquire a permit
    std::cout << "Worker " << id << " acquired a permit.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    std::cout << "Worker " << id << " releasing a permit.\n";
    sem.release(); // Release the permit
}

int main() {
    std::vector<std::thread> workers;
    for (int i = 1; i <= 5; ++i) {
        workers.emplace_back(worker, i);
    }
    for (auto& t : workers) {
        t.join();
    }
    return 0;
}


// A std::counting_semaphore named sem is created with an initial count of 3.
// Each worker thread acquires a permit before performing its work and releases the permit afterward.
// Only three workers can acquire permits at the same time, simulating limited resource availability.

