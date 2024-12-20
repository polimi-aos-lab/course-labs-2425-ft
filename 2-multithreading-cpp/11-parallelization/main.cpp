#include <iostream>
#include <functional>
#include <thread>
#include <vector>
#include <chrono>
#include <limits>

using namespace std;
using namespace std::chrono;

int sequentialFibonacci(int n)
{
    if(n<=1) return 1;
    return sequentialFibonacci(n-1)+sequentialFibonacci(n-2);
}

void parallelExecutor(const vector<function<void ()>>& tasks)
{
    vector<thread> threads;
    for(auto& f : tasks) threads.push_back(thread(f));
    for(auto& t : threads) t.join();
}

void fibImpl(int n, int& result)
{
    if(n<=1) result=1;
    else {
        int a,b;
        parallelExecutor({ [&](){ fibImpl(n-1,a); }, [&](){ fibImpl(n-2,b); } });
        result=a+b;
    }
}

int parallelFibonacci(int n)
{
    int result;
    fibImpl(n,result);
    return result;
}



void benchmark(function<int ()> f)
{
    long long best=numeric_limits<long long>::max();
    const int iterations=100;
    for(int i=0;i<iterations;i++)
    {
        auto start=steady_clock::now();
        f();
        auto stop=steady_clock::now();
        long long ns=duration_cast<nanoseconds>(stop-start).count();
        best=min(best,ns);
    }
    cout << "best time = " << best << "ns\n";
}

int main()
{
    cout << "parallel   "; benchmark([=](){ return parallelFibonacci(10); });
    cout << "sequential "; benchmark([=](){ return sequentialFibonacci(10); });
}
