#include <iostream>
#include <iomanip>
#include <map>
#include <iterator>
#include <algorithm>
#include <numeric>

using namespace std;

struct meme {
    string description;
    size_t year;
};

istream& operator>>(istream &is, meme &m) {
    return is >> quoted(m.description) >> m.year;
}

istream& operator >>(istream &is, pair<string, meme> &p) {
    return is >> quoted(p.first) >> p.second;
}

int main()
{
    map<string, meme> m;

    copy(istream_iterator<pair<string, meme>>{cin}, {}, inserter(m, end(m)));

    auto max_func ([](size_t old_max, const auto &b) {
        return max(old_max, b.first.length());
    });
    const size_t width {accumulate(begin(m), end(m), 0u, max_func)};

    for (const auto &[meme_name, meme_desc] : m) {
        const auto &[desc, year] = meme_desc;

        cout << left << setw(width) << meme_name
             << " : " << desc
             << ", " << year << '\n';
    }
}
