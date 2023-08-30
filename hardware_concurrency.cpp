#include <iostream>
#include <thread>

int main() {
    
    std::cout << "Number of hardware threads: " << std::thread::hardware_concurrency()<< std::endl;
    
    return 0;
}
