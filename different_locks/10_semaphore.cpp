// In C++, semaphores are used to manage access to a shared resource 
// by multiple threads in a concurrent programming environment. 
// A semaphore maintains a counter that indicates the number of available 
// resources or permits. Threads can acquire or release these permits, 
// ensuring controlled access to the shared resource.

// While the C++ Standard Library (as of C++20) does not include native support 
// for semaphores, they are available in the form of std::counting_semaphore and 
// std::binary_semaphore in the C++20 standard. If you are using a pre-C++20 standard, 
// you can use third-party libraries like Boost or implement semaphores manually using 
// mutexes and condition variables.