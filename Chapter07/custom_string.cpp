#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

static constexpr char tolow(char c) {
    switch (c) {
    case 'A'...'Z': return c - 'A' + 'a';
    default:        return c;
    }
}

class lc_traits : public char_traits<char> {
public:
    static constexpr void assign( char_type& r, const char_type& a ) {
        r = tolow(a);
    }

    static char_type* copy(char_type* dest, const char_type* src, size_t count) {
        transform(src, src + count, dest, tolow);
        return dest;
    }
};

class ci_traits : public char_traits<char> {
public:
    static constexpr bool eq(char_type a, char_type b) {
        return tolow(a) == tolow(b);
    }

    static constexpr bool lt(char_type a, char_type b) {
        return tolow(a) < tolow(b);
    }

    static constexpr int compare(const char_type* s1,
                                 const char_type* s2,
                                 size_t count) {
        for (; count; ++s1, ++s2, --count) {
            const char_type diff (tolow(*s1) - tolow(*s2));
            if      (diff < 0) { return -1; }
            else if (diff > 0) { return +1; }
        }
        return 0;
    }

    static constexpr const char_type* find(const char_type* p,
                                           size_t count,
                                           const char_type& ch) {
        const char_type find_c {tolow(ch)};

        for (; count != 0; --count, ++p) {
            if (find_c == tolow(*p)) { return p; }
        }

        return nullptr;
    }
};

using lc_string = basic_string<char, lc_traits>;
using ci_string = basic_string<char, ci_traits>;

ostream& operator<<(ostream& os, const lc_string& str) {
    return os.write(str.data(), str.size());
}

ostream& operator<<(ostream& os, const ci_string& str) {
    return os.write(str.data(), str.size());
}

int main()
{
    lc_string e {"Foo Bar Baz"};

    cout << "   string: "
         <<    string{"Foo Bar Baz"} << '\n'
         << "lc_string: "
         << lc_string{"Foo Bar Baz"} << '\n'
         << "ci_string: "
         << ci_string{"Foo Bar Baz"} << '\n';

    ci_string user_input {"MaGiC PaSsWoRd!"};
    ci_string password   {"magic password!"};

    if (user_input == password) {
        cout << "Passwords match: \"" << user_input
             << "\" == \"" << password << "\"\n";
    }
}
