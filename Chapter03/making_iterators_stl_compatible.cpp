#include <iostream>
#include <algorithm>

class num_iterator
{
    int i;
public:

    explicit num_iterator(int position = 0) : i{position} {}

    int operator*() const { return i; }

    num_iterator& operator++() {
        ++i;
        return *this;
    }

    bool operator!=(const num_iterator &other) const {
        return i != other.i;
    }

    bool operator==(const num_iterator &other) const {
        return !(*this !=other);
    }
};

namespace std {

// By overloading this traits structure we help STL algorithms
// accessing type definitions for our custom iterator.
// Another way is to put the following type definitions into
// the iterator class.

template <>
struct iterator_traits<num_iterator> {
    using iterator_category = std::forward_iterator_tag;
    using value_type        = int;

    // This type can be used to tell the difference between two
    // iterators. This of course only makes sense if we define
    // the difference operation for our iterator (and operator+ etc.)
    using difference_type   = int;

    // What is the correct pointer type to the individual objects
    // we are iterating over?
    using pointer           = int*;

    // Same as before, but for references.
    using reference         = int&;
};

}

class num_range {
    int a;
    int b;

public:
    num_range(int from, int to)
        : a{from}, b{to}
    {}

    num_iterator begin() const { return num_iterator{a}; }
    num_iterator end()   const { return num_iterator{b}; }
};

int main()
{
    num_range r {100, 110};

    auto [min_it, max_it] (std::minmax_element(std::begin(r), std::end(r)));
    std::cout << *min_it << " - " << *max_it << '\n';
}
