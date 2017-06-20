#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <tuple>

using namespace std;

template <typename It>
tuple<It, char, size_t> occurrences(It it, It end_it)
{
    if (it == end_it) { return {it, '?', 0}; }

    const char c {*it};
    const auto diff (find_if(it, end_it, [c](char x) { return c != x; }));

    return {diff, c, distance(it, diff)};
}

string compress(const string &s)
{
    const auto end_it (end(s));
    stringstream r;

    for (auto it (begin(s)); it != end_it;) {
        const auto [next_diff, c, n] (occurrences(it, end_it));
        r << c << n;
        it = next_diff;
    }

    return r.str();
}

string decompress(const string &s)
{
    stringstream ss{s};
    stringstream r;

    char c;
    size_t n;
    while (ss >> c >> n) {
        r << string(n, c);
    }

    return r.str();
}

int main()
{
    string s {"a00000"};
    cout << compress(s) << '\n';
    cout << decompress(compress(s)) << '\n';
}
