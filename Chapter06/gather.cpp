#include <iostream>
#include <algorithm>
#include <string>
#include <functional>

using namespace std;

template <typename It, typename F>
pair<It, It> gather(It first, It last, It gather_pos, F predicate)
{
    return {stable_partition(first, gather_pos, not_fn(predicate)),
            stable_partition(gather_pos,  last,        predicate)};
}

template <typename It>
void gather_sort(It first, It last, It gather_pos)
{
    // Errata: The original book version let the user provide a
    // comparison function.
    // That comparison function was used in one of the sort calls
    // and a negated version was used in the other.
    // Unfortunately, the negated version of the comparison function
    // does not follow the strict weak ordering requirement from the
    // standard, which means that that version can lead to
    // undefined behavior.
    // The current version uses less and greater, which fix this.

    using T = typename std::iterator_traits<It>::value_type;
    stable_sort(first, gather_pos, greater<T>{});
    stable_sort(gather_pos,  last, less<T>{});
}

int main()
{
    auto is_a ([](char c) { return c == 'a'; });
    string a {"a_a_a_a_a_a_a_a_a_a_a"};

    auto middle (begin(a) + a.size() / 2);

    gather(begin(a), end(a), middle, is_a);
    cout << a << '\n';

    gather(begin(a), end(a), begin(a), is_a);
    cout << a << '\n';

    gather(begin(a), end(a), end(a), is_a);
    cout << a << '\n';

    // This will NOT work as naively expected
    gather(begin(a), end(a), middle, is_a);
    rotate(begin(a), begin(a) + 1, end(a));
    cout << a << '\n';

    string b {"_9_2_4_7_3_8_1_6_5_0_"};
    gather_sort(begin(b), end(b), begin(b) + b.size() / 2);
    cout << b << '\n';
}
