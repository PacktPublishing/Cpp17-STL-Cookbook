#include <iostream>
#include <chrono>
#include <ratio>
#include <cmath>
#include <iomanip>
#include <optional>

using namespace std;

using seconds      = chrono::duration<double>;
using milliseconds = chrono::duration<double, ratio_multiply<seconds::period, milli>>;
using microseconds = chrono::duration<double, ratio_multiply<seconds::period, micro>>;

static pair<string, seconds> get_input()
{
    string s;

    const auto tic (chrono::steady_clock::now());
    if (!(cin >> s)) {
        return {{}, {}};
    }
    const auto toc (chrono::steady_clock::now());

    return {s, toc - tic};
}

int main()
{
    while (true) {
        cout << "Please type the word \"C++17\" as fast as you can.\n> ";

        const auto [user_input, diff] = get_input();

        if (user_input == "") { break; }

        if (user_input == "C++17") {
            cout << "Bravo. You did it in:\n" << fixed << setprecision(2)
                  << setw(12) <<               diff.count() << " seconds.\n"
                  << setw(12) << milliseconds(diff).count() << " milliseconds.\n"
                  << setw(12) << microseconds(diff).count() << " microseconds.\n";
            break;
        } else {
            cout << "Sorry, your input does not match. You may try again.\n";
        }
    }
}
