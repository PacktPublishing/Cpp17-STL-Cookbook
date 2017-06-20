#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

template <typename InIt, typename OutIt, typename T, typename F>
InIt split(InIt it, InIt end_it, OutIt out_it, T split_val, F bin_func)
{
    while (it != end_it) {
        auto slice_end (find(it, end_it, split_val));
        *out_it++ = bin_func(it, slice_end);

        if (slice_end == end_it) { return end_it; }
        it = next(slice_end);
    }
    return it;
}

int main()
{
    const string s {"a-b-c-d-e-f-g"};

    auto binfunc ([](auto it_a, auto it_b) {
        return string(it_a, it_b);
    });

    list<string> l;

    split(begin(s), end(s), back_inserter(l), '-', binfunc);

    copy(begin(l), end(l), ostream_iterator<string>{cout, "\n"});

    return 0;
}
