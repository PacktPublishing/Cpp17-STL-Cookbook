#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

static size_t entry_size(const directory_entry &entry)
{
    if (!is_directory(entry)) { return file_size(entry); }

    return accumulate(directory_iterator{entry}, {}, 0u,
        [](size_t accum, const directory_entry &e) {
            return accum + entry_size(e);
        });
}

static string size_string(size_t size)
{
    stringstream ss;
    if      (size >= 1000000000) { ss << (size / 1000000000) << 'G'; }
    else if (size >= 1000000)    { ss << (size / 1000000)    << 'M'; }
    else if (size >= 1000)       { ss << (size / 1000)       << 'K'; }
    else { ss << size << 'B'; }

    return ss.str();
}

int main(int argc, char *argv[])
{
    path dir {argc > 1 ? argv[1] : "."};

    if (!exists(dir)) {
        cout << "Path " << dir << " does not exist.\n";
        return 1;
    }

    for (const auto &entry : directory_iterator{dir}) {
        cout << setw(5) << right << size_string(entry_size(entry))
             << " " << entry.path().filename().c_str() << '\n';
    }
}
