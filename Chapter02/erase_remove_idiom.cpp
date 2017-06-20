#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> v {1, 2, 3, 2, 5, 2, 6, 2, 4, 8};

    {
        const auto new_end (remove(begin(v), end(v), 2));
        v.erase(new_end, end(v));
    }

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << '\n';

    {
        const auto odd ([](int i) { return i % 2 != 0; });
        const auto new_end (remove_if(begin(v), end(v), odd));
        v.erase(new_end, end(v));
    }

    v.shrink_to_fit();

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << '\n';
}
