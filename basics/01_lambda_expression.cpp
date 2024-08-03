#include <iostream>

/*
C++ Lambda expression allows us to define anonymous function objects
(functors) which can either be used inline or passed as an argument.

syntax ->
auto greet = []() {
  // lambda function body
};

[] -> lambda initialiser : denotes the start of the lambda expression
() -> paramter list :
*/

int main()
{
  // getting started with lambda expressions
  auto greet = []()
  {
    std::cout << "i am a lambda expression\n";
  };

  greet();

  // parameters & lambda expressions
  auto sum = [](int a, int b)
  {
    return a + b;
  };

  std::cout << sum(2, 3) << std::endl;

  // C++ Lambda Function With Return Type

  auto sum2 = [](int a, double b) -> double
  {
    return (a + b);
  };

  std::cout << sum2(2, 3.2) << std::endl;

  // C++ Lambda Function Capture Clause
  // By default, lambda functions cannot access variables of the enclosing function.
  // In order to access those variables, we use the capture clause.

  int x = 9;

  auto printX = [x]() {
    std::cout<<x<<std::endl;
  };

  // to access all variables inside capture clause keep -> &
    auto printX2 = [&]() {
    std::cout<<x<<std::endl;
  };
}