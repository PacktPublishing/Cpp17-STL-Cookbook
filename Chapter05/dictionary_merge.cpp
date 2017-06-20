#include <iostream>
#include <algorithm>
#include <iterator>
#include <deque>
#include <tuple>
#include <string>
#include <fstream>

using namespace std;

using dict_entry = pair<string, string>;

namespace std {
ostream& operator<<(ostream &os, const dict_entry p)
{
    return os << p.first << " " << p.second;
}

istream& operator>>(istream &is, dict_entry &p)
{
    return is >> p.first >> p.second;
}
}

template <typename IS>
deque<dict_entry> from_instream(IS &&is)
{
    deque<dict_entry> d {istream_iterator<dict_entry>{is}, {}};
    sort(begin(d), end(d));
    return d;
}

int main()
{
    ifstream file_in {"dict.txt"};

    const auto dict1 (from_instream(ifstream{"dict.txt"}));
    const auto dict2 (from_instream(cin));

    merge(begin(dict1), end(dict1),
          begin(dict2), end(dict2),
          ostream_iterator<dict_entry>{cout, "\n"});
}
