#include <exception>
#include <future>
#include <iostream>
#include <math.h>
#include <mutex>
#include <thread>

using namespace std;

double calculate_pi(int terms) {

  if (terms < 1) {
    throw runtime_error("pehle fursat mei nikal");
  }
  double sum = 0.0;
  for (int i = 0; i < terms; i++) {
    int exp = pow(-1, i);
    double term = (1.0 / (2 * i + 1));
    sum += (exp * term * 4);
  }
  return sum;
}

int main() {
  promise<double> promise;
  auto do_pi = [&](int terms) {
    try {
      auto result = calculate_pi(terms);
      promise.set_value(result);
    } catch (...) {
      promise.set_exception(current_exception());
    }
  };

  thread t1(do_pi, -1);

  future<double> future = promise.get_future();

  try {
    cout << future.get() << endl;
  } catch (const exception &e) {
    cout << e.what() << endl;
  }

  t1.join();
}