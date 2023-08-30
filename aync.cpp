#include <iostream>
#include <future> // This is where the asynchronous stuff is
#include<thread>
#include<chrono>

// Your friend bakes the cake asynchronously
int bakeCake() {
    std::this_thread::sleep_for(std::chrono::seconds(5)); // Pretend baking takes 5 seconds
    return 1; // 1 means the cake is ready
}

int main() {
    // You ask your friend to bake the cake (start the baking process)
    std::future<int> cakeFuture = std::async(std::launch::async, bakeCake);

    // You continue doing your own stuff (like playing games)
    std::cout << "Waiting for the cake to be ready..." << std::endl;

    // When you're ready to eat the cake, you check if it's ready
    int cakeStatus = cakeFuture.get(); // This line waits until the cake is ready

    if (cakeStatus == 1) {
        std::cout << "Yay! The cake is ready. Let's eat!" << std::endl;
    }

    return 0;
}
