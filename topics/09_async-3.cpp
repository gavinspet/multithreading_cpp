// Compiler-Deciding Launch
// If you don't specify a launch policy, 
// the compiler decides whether to run the function asynchronously or deferred. 
// This decision is usually based on the system's current load and available resources.

#include <iostream>
#include <future>
#include <thread>

// Function to be called asynchronously
int asyncFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x * x;
}

int main() {
    // Launch the function with the compiler deciding the launch policy
    std::future<int> result = std::async(asyncFunction, 10);

    // Do other work here...

    // Get the result (this will block if the result is not ready)
    std::cout << "Result: " << result.get() << std::endl;

    return 0;
}
