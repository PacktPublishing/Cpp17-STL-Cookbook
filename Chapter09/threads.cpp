#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono_literals;

static void thread_with_param(int i)
{
    this_thread::sleep_for(1ms * i);

    cout << "Hello from thread " << i << '\n';

    this_thread::sleep_for(1s * i);

    cout << "Bye from thread " << i << '\n';
}

int main()
{
    cout << thread::hardware_concurrency()
         << " concurrent threads are supported.\n";

    thread t1 {thread_with_param, 1};
    thread t2 {thread_with_param, 2};
    thread t3 {thread_with_param, 3};

    t1.join();
    t2.join();
    t3.detach();

    cout << "Threads joined.\n";
}
