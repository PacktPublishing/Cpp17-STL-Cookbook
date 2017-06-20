#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

using namespace std;

int main()
{
    istream_iterator<int> it_cin {cin};
    istream_iterator<int> end_cin;

    deque<int> v;

    copy(it_cin, end_cin, back_inserter(v));

    istringstream sstr {"123 456 789"};
    auto deque_middle (next(begin(v), static_cast<int>(v.size()) / 2));

    copy(istream_iterator<int>{sstr}, {}, inserter(v, deque_middle));

    initializer_list<int> il2 {-1, -2, -3};
    copy(begin(il2), end(il2), front_inserter(v));

    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << '\n';
}
