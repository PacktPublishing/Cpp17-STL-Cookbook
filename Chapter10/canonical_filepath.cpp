#include <iostream>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

int main()
{
    path p {"testdir/foobar.txt"};

    cout << "current_path    : " << current_path()     << '\n'
         << "absolute_path   : " << absolute(p)        << '\n'
         << "system_complete : " << system_complete(p) << '\n';

    cout << path{"testdir"} / "foobar.txt" << '\n';

    cout << "canonical testdir   : "
         << canonical("foobar.txt", current_path() / "testdir") << '\n'
         << "canonical testdir 2 : "
         << canonical(p, current_path() / "testdir/..") << '\n';

    cout << "equivalence: "
         << equivalent("testdir/foobar.txt",
                       "testdir/../testdir/foobar.txt") << '\n';



}
