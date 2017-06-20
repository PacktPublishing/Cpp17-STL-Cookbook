#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

static tuple<path, file_status, size_t> file_info(const directory_entry &entry)
{
    const auto fs (status(entry));
    return {entry.path(),
            fs,
            is_regular_file(fs) ? file_size(entry.path()) : 0u};

}

static char type_char(file_status fs)
{
    if      (is_directory(fs))      { return 'd'; }
    else if (is_symlink(fs))        { return 'l'; }
    else if (is_character_file(fs)) { return 'c'; }
    else if (is_block_file(fs))     { return 'b'; }
    else if (is_fifo(fs))           { return 'p'; }
    else if (is_socket(fs))         { return 's'; }
    else if (is_other(fs))          { return 'o'; }
    else if (is_regular_file(fs))   { return 'f'; }

    return '?';
}

static string rwx(perms p)
{
    auto check ([p](perms bit, char c) { return (p & bit) == perms::none ? '-' : c; });

    return {check(perms::owner_read,   'r'),
            check(perms::owner_write,  'w'),
            check(perms::owner_exec,   'x'),
            check(perms::group_read,   'r'),
            check(perms::group_write,  'w'),
            check(perms::group_exec,   'x'),
            check(perms::others_read,  'r'),
            check(perms::others_write, 'w'),
            check(perms::others_exec,  'x')};
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

    vector<tuple<path, file_status, size_t>> items;

    transform(directory_iterator{dir}, {}, back_inserter(items), file_info);

    for (const auto &[path, status, size]: items) {
        cout << type_char(status) << rwx(status.permissions()) << "  "
             << setw(4) << right << size_string(size) << "  "
             << path.filename().c_str() << '\n';
    }
}
