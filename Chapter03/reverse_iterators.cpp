#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int main()
{
    list<int> l {1, 2, 3, 4, 5};

    copy(l.rbegin(), l.rend(), ostream_iterator<int>{cout, ", "});
    std::cout << '\n';

    copy(make_reverse_iterator(end(l)),
         make_reverse_iterator(begin(l)),
         ostream_iterator<int>{cout, ", "});
    std::cout << '\n';
}
