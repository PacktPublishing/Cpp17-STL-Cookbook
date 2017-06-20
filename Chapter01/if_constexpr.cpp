#include <cassert>
#include <string>
#include <vector>
#include <cstdio>

template <typename T>
class addable
{
    T val;

public:
    addable(T v) : val{v} {}

#if 0
    // The C++11 way
    template <typename U>
    std::enable_if_t<!std::is_same<T, std::vector<U>>::value, T>
    add(U x) const { return val + x; }

    template <typename U>
    std::enable_if_t<std::is_same<T, std::vector<U>>::value, std::vector<U>>
    add(U x) const {
        auto copy = val;
        for (auto &n : copy) {
            n += x;
        }
        return copy;
    }
#else
    // The C++17 way
    template <typename U>
    T add(U x) const {
        if constexpr (std::is_same_v<T, std::vector<U>>) {
            auto copy = val;
            for (auto &n : copy) {
                n += x;
            }
            return copy;
        } else {
            return val + x;
        }
    }
#endif

};

int main()
{
    using namespace std::string_literals;

    assert(addable<int>{2}.add(3) == 5);
    assert(addable<std::string>{"aa"s}.add("bb"s) == "aabb"s);

    std::vector<int> v1 {1, 2, 3};
    std::vector<int> v2 {11, 12, 13};
    assert(addable<std::vector<int>>{v1}.add(10) == v2);

    std::vector<std::string> sv1 {"a", "b", "c"};
    std::vector<std::string> sv2 {"az", "bz", "cz"};
    assert(addable<std::vector<std::string>>{sv1}.add("z"s) == sv2);
}
