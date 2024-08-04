#include <future>
#include <iostream>
#include <thread>

// Function to calculate the sum of two numbers and store the result in a
// promise
void calculateSum(std::promise<int> &prom, int a, int b) {
  int sum = a + b;
  // Set the result in the promise
  prom.set_value(sum);
}

int main() {
  int a = 5;
  int b = 7;

  // Create a promise and get a future associated with it
  std::promise<int> sumPromise;
  std::future<int> sumFuture = sumPromise.get_future();

  // Start a thread to calculate the sum asynchronously
  std::thread sumThread(calculateSum, std::move(sumPromise), a, b);

  // Do some other work while the sum is being calculated in the background

  // Wait for the result by calling get() on the future
  int result = sumFuture.get();

  // The result is now available
  std::cout << "The sum of " << a << " and " << b << " is: " << result
            << std::endl;

  // Clean up
  sumThread.join();

  return 0;
}
