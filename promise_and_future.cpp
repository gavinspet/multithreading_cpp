#include<iostream>
#include<thread>
#include<math.h>
#include<mutex>
#include<future>

using namespace std;

double calculate_pi(int terms)
{
    double sum = 0.0;
    for(int i=0;i<terms; i++)
    {
        int exp = pow(-1,i);
        double term = (1.0/(2*i+1));
        sum+= (exp*term*4);
    }
    return sum;
}

int main()
{
    promise<double> promise;
    auto do_pi= [&](int terms)
    {
        auto result = calculate_pi(terms);

        promise.set_value(result);
    };

    future<double> future = promise.get_future();

    cout<<future.get()<<endl;

}