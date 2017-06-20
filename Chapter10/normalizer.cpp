#include <iostream>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <path>\n";
        return 1;
    }

    path dir {argv[1]};

    if (!exists(dir)) {
        cout << "Path " << dir << " does not exist.\n";
        return 1;
    }

    cout << canonical(dir).c_str() << '\n';
}
