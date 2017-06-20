#include <iostream>
#include <iomanip>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

struct city {
    string name;
    size_t population;
    double latitude;
    double longitude;
};

istream& operator>>(istream &is, city &c)
{
    is >> ws;
    getline(is, c.name);
    is >> c.population >> c.latitude >> c.longitude;
    return is;
}

int main()
{
    vector<city> l;

    copy(istream_iterator<city>{cin}, {}, back_inserter(l));

    for (const auto &[name, pop, lat, lon] : l) {
        cout << left << setw(15) << name
             << " population=" << pop
             << " lat=" << lat
             << " lon=" << lon << '\n';
    }
}
