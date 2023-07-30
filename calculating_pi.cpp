#include <iostream>
#include <math.h>

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
    cout<<calculate_pi(12345678)<<endl;
}