#include <iostream>
#include <tuple>
#include <map>
#include <stdexcept>

bool divide_remainder(int dividend, int divisor, int &fraction, int &remainder)
{
    if (divisor == 0) {
        return false;
    }
    fraction  = dividend / divisor;
    remainder = dividend % divisor;
    return true;
}

std::pair<int, int> divide_remainder(int dividend, int divisor)
{
    if (divisor == 0) {
        throw std::runtime_error{"Attempt to divide by 0"};
    }
    return {dividend / divisor, dividend % divisor};
}

int main()
{
    { // old school way
        int fraction, remainder;
        const bool success {divide_remainder(16, 3, fraction, remainder)};
        if (success) {
            std::cout << "16 / 3 is " << fraction << " with a remainder of " << remainder << "\n";
        }
    }

    { // C++11 way
        const auto result (divide_remainder(16, 3));
        std::cout << "16 / 3 is " << result.first << " with a remainder of " << result.second << "\n";
    }

    { // C++11, ignoring fraction part of result
        int remainder;
        std::tie(std::ignore, remainder) = divide_remainder(16, 5);
        std::cout << "16 % 5 is " << remainder << "\n";
    }

    { // C++17, use structured bindings
        auto [fraction, remainder] = divide_remainder(16, 3);
        std::cout << "16 / 3 is " << fraction << " with a remainder of " << remainder << "\n";
    }

    { // C++17, decompose a tuple into individual vars
        std::tuple<int, float, long> tup {1, 2.0, 3};
        auto [a, b, c] = tup;
        std::cout << a << ", " << b << ", " << c << "\n";
    }

    { // C++17, use structured binding in for-loop

        std::map<std::string, size_t> animal_population {
            {"humans",   7000000000},
            {"chickens", 17863376000},
            {"camels",   24246291},
            {"sheep",    1086881528}
            /* … */
        };

        for (const auto &[species, count] : animal_population) {
                std::cout << "There are " << count << " " << species << " on this planet.\n";
        }
    }
}
