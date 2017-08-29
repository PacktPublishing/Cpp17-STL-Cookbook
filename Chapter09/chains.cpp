#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <sstream>
#include <future>

using namespace std;
using namespace chrono_literals;

struct pcout : public stringstream {
    static inline mutex cout_mutex;

    ~pcout() {
        lock_guard<mutex> l {cout_mutex};
        cout << rdbuf();
        cout.flush();
    }
};

// create(...), concat(...), and twice(...) are our 3 workhorse
// functions that we want to parallelize.
// In order to be really simple for the sake of being just examples, they
// just do simple string operations and return the result.
// These functions do also simulate large amounts of work by sleeping for
// several seconds. This way it makes sense to let them run in parallel.
// (Of course if a thread sleeps for N seconds, it does not occupy a whole
// core for that time - it is just suspended giving space for other threads)

static string create(const char *s)
{
    pcout{} << "3s CREATE " << quoted(s) << '\n';
    this_thread::sleep_for(3s);
    return {s};
}

static string concat(const string &a, const string &b)
{
    pcout{} << "5s CONCAT "
          << quoted(a) << " "
          << quoted(b) << '\n';
    this_thread::sleep_for(5s);
    return a + b;
}

static string twice(const string &s)
{

    pcout{} << "3s TWICE  " << quoted(s) << '\n';
    this_thread::sleep_for(3s);
    return s + s;
}

template <typename F>
static auto asynchronize(F f)
{
    return [f](auto ... xs) {
        return [=] () {
            return async(launch::async, f, xs...);
        };
    };
}

template <typename F>
static auto fut_unwrap(F f)
{
    return [f](auto ... xs) {
        return f(xs.get()...);
    };
}

template <typename F>
static auto async_adapter(F f)
{
    return [f](auto ... xs) {
        return [=] () {
            return async(launch::async, fut_unwrap(f), xs()...);
        };
    };
}

int main()
{
    auto pcreate (asynchronize(create));
    auto pconcat (async_adapter(concat));
    auto ptwice  (async_adapter(twice));

    auto result (
        pconcat(
            ptwice(
                pconcat(
                    pcreate("foo "),
                    pcreate("bar "))),
            pconcat(
                pcreate("this "),
                pcreate("that "))));

    cout << "Setup done. Nothing executed yet.\n";

    cout << result().get() << '\n';
}
