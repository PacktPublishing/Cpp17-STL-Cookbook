#include <iostream>
#include <regex>
#include <vector>
#include <experimental/filesystem>

using namespace std;
using namespace experimental::filesystem;

template <typename T>
static string replace(string s, const T &replacements)
{
    for (const auto &[pattern, repl] : replacements) {
        s = regex_replace(s, pattern, repl);
    }

    return s;
}

int main(int argc, char *argv[])
{
    if (argc < 3 || argc % 2 != 1) {
        cout << "Usage: " << argv[0] << " <pattern> <replacement> ...\n";
        return 1;
    }

    vector<pair<regex, string>> patterns;

    for (int i {1}; i < argc; i += 2) {
        patterns.emplace_back(argv[i], argv[i + 1]);
    }

    for (const auto &entry : recursive_directory_iterator{current_path()}) {
        path opath {entry.path()};
        string rname {replace(opath.filename().string(), patterns)};

        path rpath {opath};
        rpath.replace_filename(rname);

        if (opath != rpath) {
            cout << opath.c_str() << " --> " << rpath.filename().c_str() << '\n';
            if (exists(rpath)) {
                cout << "Error: Can't rename. Destination file exists.\n";
            } else {
                rename(opath, rpath);
            }
        }
    }
}
