#include <iostream>
#include <fstream>
#include <system_error>
#include <cstring>

using namespace std;

int main()
{
    ifstream f;
    f.exceptions(f.failbit | f.badbit);

    try {
        f.open("mmes.txt");

        int i;
        f >> i;

        cout << "integer has value: " << i << '\n';
    }
    catch (const ios_base::failure &e) {
        cerr << "Caught error: ";
        if (errno) {
            // This is not thread safe.
            cerr << strerror(errno) << '\n';
        } else {
            cerr << e.what() << '\n';
        }
    }
}
