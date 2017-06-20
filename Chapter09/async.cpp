#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>

using namespace std;

static map<char, size_t> histogram(const string &s)
{
    map<char, size_t> m;

    for (char c : s) { m[c] += 1; }

    return m;
}

static string sorted(string s)
{
    sort(begin(s), end(s));
    return s;
}

static bool is_vowel(char c)
{
    char vowels[] {"aeiou"};
    return end(vowels) != find(begin(vowels), end(vowels), c);
}

static size_t vowels(const string &s)
{
    return count_if(begin(s), end(s), is_vowel);
}

int main()
{
    cin.unsetf(ios::skipws);
    string input {istream_iterator<char>{cin}, {}};
    input.pop_back();

    auto hist        (async(launch::async, histogram, input));
    auto sorted_str  (async(launch::async, sorted, input));
    auto vowel_count (async(launch::async, vowels, input));

    for(const auto &[c, count] : hist.get()) {
        cout << c << ": " << count << '\n';
    }

    cout << "Sorted string: " << quoted(sorted_str.get()) << '\n';
    cout << "Total vowels: " << vowel_count.get() << '\n';
}
