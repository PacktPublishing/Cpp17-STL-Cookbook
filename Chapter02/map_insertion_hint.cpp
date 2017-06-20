#include <iostream>
#include <map>
#include <string>

using namespace std;

using map_type = map<string, size_t>;

int main()
{
    map_type m {{"b", 1}, {"c", 2}, {"d", 3}};

    auto insert_it (end(m));
    for (const auto &s : {"z", "y", "x", "w", "v"}) {
        insert_it = m.insert(insert_it, {s, 1});
    }

    // In this example line, the hint is wrong.
    // It points past the last element, but the "0" string will be inserted
    // at the front. Therefore it does not have a better runtime performance
    // than insert without a hint parameter!
    m.insert(end(m), {"a", 1});

    for (const auto & [key, value] : m) {
        std::cout << "\"" << key << "\": " << value << ", ";
    }
    std::cout << '\n';
}

