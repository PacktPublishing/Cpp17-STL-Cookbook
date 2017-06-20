#include <iostream>
#include <optional>

using namespace std;

using oint = optional<int>;

oint read_int()
{
    int i;
    if (cin >> i) { return {i}; }
    return {};
}

oint operator+(oint a, oint b)
{
    if (!a || !b) { return {}; }

    return {*a + *b};
}

oint operator+(oint a, int b)
{
    if (!a) { return {}; }

    return {*a + b};
}

int main()
{
    cout << "Please enter 2 integers.\n> ";

    auto a {read_int()};
    auto b {read_int()};

    auto sum (a + b + 10);

    if (sum) {
        cout << *a << " + " << *b << " + 10 = "
             << *sum << '\n';
    } else {
        cout << "sorry, the input was "
                "something else than 2 numbers.\n";
    }

}
