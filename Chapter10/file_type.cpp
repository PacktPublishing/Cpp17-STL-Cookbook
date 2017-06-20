#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

static string size_string(size_t size)
{
    stringstream ss;
    if      (size >= 1000000000) { ss << (size / 1000000000) << 'G'; }
    else if (size >= 1000000)    { ss << (size / 1000000)    << 'M'; }
    else if (size >= 1000)       { ss << (size / 1000)       << 'K'; }
    else { ss << size << 'B'; }

    return ss.str();
}

static map<string, pair<size_t, size_t>> ext_stats(const path dir)
{
    map<string, pair<size_t, size_t>> m;

    for (const auto &entry : recursive_directory_iterator{dir}) {
        const path        p  {entry.path()};
        const file_status fs {status(p)};

        if (is_directory(fs)) { cout << "skipping " << p << '\n'; continue; }

        const string ext {p.extension().string()};

        if (ext.length() == 0) { continue; }

        const size_t size {file_size(p)};

        auto &[size_accum, count] = m[ext];

        size_accum += size;
        count += 1;
    }

    return m;
}

int main(int argc, char *argv[])
{
    path dir {argc > 1 ? argv[1] : "."};

    if (!exists(dir)) {
        cout << "Path " << dir << " does not exist.\n";
        return 1;
    }

    for (const auto &[ext, stats] : ext_stats(dir)) {
        const auto &[accum_size, count] = stats;

        cout << setw(15) << left <<  ext << ": "
             << setw(4) << right << count << " items, avg size "
             << setw(4) << size_string(accum_size / count) << '\n';
    }
}
