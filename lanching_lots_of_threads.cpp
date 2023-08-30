#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
#include <vector>

using namespace std;

mutex mtx;

int work(int id)
{
    unique_lock<mutex> lock(mtx);
    cout<<"Starting thread"<<id<<endl;
    lock.unlock();
    return id;

    this_thread::sleep_for(chrono::seconds(3));
}

int main()
{

  vector<shared_future<int>> v;

 for(int i = 0; i< thread::hardware_concurrency(); i++)
 {
   shared_future<int> f = async(launch::async, work, i);
   v.push_back(f);
 }

    for(auto f: v)
    {
        cout << "Returned: " << f.get() << endl;
    }

}