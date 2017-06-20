#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

once_flag callflag;
mutex cout_mutex;

static void once_print(size_t x)
{
    cout << '!';
}

static void print(size_t x)
{
    std::call_once(callflag, once_print, x);
    cout << x;
}

int main()
{
    vector<thread> v;

    for (size_t i {0}; i < 10; ++i) {
        v.emplace_back(print, i);
    }

    for (auto &t : v) { t.join(); }

    cout << '\n';
}
