#include <iostream>
#include <string_view>

using namespace std;

void print(string_view v)
{
    // note: do not expect a null terminated string
    const auto words_begin (v.find_first_not_of(" \t\n"));
    v.remove_prefix(min(words_begin, v.size()));

    const auto words_end   (v.find_last_not_of(" \t\n"));

    if (words_end != string_view::npos) {
        v.remove_suffix(v.size() - words_end - 1);
    }

    cout << "length: " << v.length()
         << " [" << v << "]\n";
}

int main(int argc, char *argv[])
{
    print(argv[0]);
    print({});
    print("a const char * array");
    print("an std::string_view literal"sv);
    print("an std::string instance"s);

    print("   \t\n foobar  \n  \t ");

    char cstr[] {'a', 'b', 'c'}; // no null termination
    print(string_view(cstr, sizeof(cstr)));
}

