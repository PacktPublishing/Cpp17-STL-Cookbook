#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void quick_remove_at(std::vector<T> &v, std::size_t idx)
{
    if (idx < v.size()) {
        v.at(idx) = std::move(v.back());
        v.pop_back();
    }
}

template <typename T>
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it)
{
    if (it != std::end(v)) {
        *it = std::move(v.back());
        v.pop_back();
    }
}


int main()
{
    std::vector<int> v {123, 456, 789, 100, 200};

    quick_remove_at(v, 2);

    for (int i : v) {
        std::cout << i << ", ";
    }
    std::cout << '\n';

    quick_remove_at(v, std::find(std::begin(v), std::end(v), 123));

    for (int i : v) {
        std::cout << i << ", ";
    }
    std::cout << '\n';

    std::vector<int> vv;

    quick_remove_at(vv, 0);
}
