#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
size_t wordcount(T &is)
{
    return distance(istream_iterator<string>{is}, {});
}

int main(int argc, char **argv)
{
    size_t wc;
    if (argc == 2) {
        ifstream ifs {argv[1]};
        wc = wordcount(ifs);
    } else {
        wc = wordcount(cin);
    }

    cout << "There are " << wc << " words\n";
};
