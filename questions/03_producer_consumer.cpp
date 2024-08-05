#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

const int BUFFER_SIZE = 10;
std::queue<int> buffer;

std::mutex mtx;
std::condition_variable cv_producer;
std::condition_variable cv_consumer;

void producer() {
    int data = 0;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_producer.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        data++;
        buffer.push(data);
        std::cout << "Produced: " << data << std::endl;

        cv_consumer.notify_one();
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv_consumer.wait(lock, [] { return !buffer.empty(); });

        int data = buffer.front();
        buffer.pop();
        std::cout << "Consumer " << id << " consumed: " << data << std::endl;

        cv_producer.notify_one();
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

int main() {
    std::thread producer_thread(producer);

    std::thread consumer_threads[] = {
        std::thread(consumer, 1),
        std::thread(consumer, 2),
        std::thread(consumer, 3)
    };

    producer_thread.join();
    for (auto& t : consumer_threads) {
        t.join();
    }

    return 0;
}
