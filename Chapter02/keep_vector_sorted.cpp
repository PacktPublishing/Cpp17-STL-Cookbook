#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <set>
#include <algorithm>
#include <iterator> // for ostream_iterator
#include <cassert>

using namespace std;

template <typename C>
void print_vector(const C &v)
{
    std::cout << "Words: {";
    copy(begin(v), end(v), ostream_iterator<typename C::value_type>(cout, " "));
    std::cout << "}\n";
}

template <typename C, typename T>
void insert_sorted(C &v, const T &word)
{
    const auto it (lower_bound(begin(v), end(v), word));
    v.insert(it, word);
}

int main()
{
    list<string> v {"some", "random", "words", "without", "order", "aaa", "yyy"};

    //assert(false == is_sorted(begin(v), end(v)));

    print_vector(v);

    //sort(begin(v), end(v));

    //assert(true == is_sorted(begin(v), end(v)));

    print_vector(v);

    insert_sorted(v, "foobar");
    insert_sorted(v, "zzz");

    print_vector(v);
}

