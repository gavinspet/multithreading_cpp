// Deferred Launch
// The deferred launch (std::launch::deferred) does not run 
// the function until the result is explicitly requested 
// (via result.get() or result.wait()).


#include <iostream>
#include <future>
#include <thread>

// Function to be called asynchronously
int asyncFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x * x;
}

int main() {
    // Launch the function in deferred mode
    std::future<int> result = std::async(std::launch::deferred, asyncFunction, 10);

    // Do other work here...

    // Get the result (this will run the function synchronously if it hasn't been run yet)
    std::cout << "Result: " << result.get() << std::endl;

    return 0;
}
