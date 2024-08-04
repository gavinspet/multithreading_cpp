#include <exception>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

double work(int terms) {
  if (terms < 0) {
    throw runtime_error("Term cannot be less than zero");
  }

  double sum = 1.2;

  for (int i = 0; i < terms; i++) {
    sum += 10.0;
  }
  return sum;
}

int main() {
  packaged_task<double(int)> pTask(work);
  future<double> fFuture = pTask.get_future();

  thread t1(move(pTask), 3);

  try {
    cout << "sum is :" << fFuture.get() << "\n";
  } catch (exception &e) {
    cout << "Error : " << e.what() << "\n";
  }

  t1.join();
  return 0;
}