#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
    string a { "a"  };
    auto   b ( "b"s );

    string_view c { "c"   };
    auto        d ( "d"sv );

    cout << a << ", " << b << '\n';
    cout << c << ", " << d << '\n';

    cout << a + b << '\n';
    cout << a + string{c} << '\n';

    ostringstream o;

    o << a << " " << b << " " << c << " " << d;
    auto concatenated (o.str());

    cout << concatenated << '\n';

    transform(begin(concatenated), end(concatenated), begin(concatenated), ::toupper);
    cout << concatenated << '\n';
}
