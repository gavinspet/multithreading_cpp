/*
Asynchronous operations in C++ can be managed using 
the std::async function from the C++11 standard library, 
which runs a function asynchronously (potentially in a new thread) 
and returns a std::future that holds the result.
*/


// standard launch

#include <iostream>
#include <future>
#include <thread>

// Function to be called asynchronously
int asyncFunction(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return x * x;
}

int main() {
    // Launch the function asynchronously
    std::future<int> result = std::async(std::launch::async, asyncFunction, 10);

    // Do other work here...

    // Get the result (this will block if the result is not ready)
    std::cout << "Result: " << result.get() << std::endl;

    return 0;
}
