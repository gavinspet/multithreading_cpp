#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class App {
private:
  mutex mtx;
  int count = 0;

public:
  auto operator()() {
    for (int i = 0; i < 10; i++) {
      const lock_guard<mutex> guard(mtx);
      count++;
    }
  }

  int getCount() { return count; }
};

int main() {
  App app;
  // app();
  // app();
  thread t1(ref(app));
  thread t2(ref(app));
  thread t3(ref(app));

  t1.join();
  t2.join();
  t3.join();

  cout << app.getCount() << endl;
}