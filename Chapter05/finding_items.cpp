#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

struct city {
    string   name;
    unsigned population;
};

bool operator==(const city &a, const city &b) {
    return a.name == b.name && a.population == b.population;
}

ostream& operator<<(ostream &os, const city &city) {
    return os << "{" << city.name << ", " << city.population << "}";
}

template <typename C>
static auto opt_print (const C &container)
{
    return [end_it (end(container))] (const auto &item) {
        if (item != end_it) {
            cout << *item << '\n';
        } else {
            cout << "<end>\n";
        }
    };
}

int main()
{
    const vector<city> c {
        {"Aachen",        246000},
        {"Berlin",       3502000},
        {"Braunschweig",  251000},
        {"Cologne",      1060000}
    };

    auto print_city (opt_print(c));

    {
        auto found_cologne (find(begin(c), end(c), city{"Cologne", 1060000}));
        print_city(found_cologne);
    }

    {
        auto found_cologne (find_if(begin(c), end(c), [] (const auto &item) {
            return item.name == "Cologne";
        }));
        print_city(found_cologne);
    }

    {
        auto population_more_than ([](unsigned i) {
            return [=] (const city &item) { return item.population > i; };
        });

        auto found_large (find_if(begin(c), end(c), population_more_than(2000000)));
        print_city(found_large);
    }

    const vector<int> v {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto print_int (opt_print(v));

    bool contains_7 {binary_search(begin(v), end(v), 7)};
    cout << contains_7 << '\n';

    auto [lower_it, upper_it] (equal_range(begin(v), end(v), 7));
    print_int(lower_it);
    print_int(upper_it);

    print_int(lower_bound(begin(v), end(v), 7));
    print_int(upper_bound(begin(v), end(v), 7));
}

