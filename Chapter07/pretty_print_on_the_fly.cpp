#include <iostream>
#include <iomanip>

using namespace std;

class format_guard {
    ostream& os;
    ios::fmtflags f;

public:
    explicit format_guard(ostream &guarded_stream = cout) : os(guarded_stream), f(os.flags()) {}
    ~format_guard() { os.flags(f); }
};


template <typename T>
struct scientific_type {
    T value;

    explicit scientific_type(T val) : value{val} {}
};

template <typename T>
ostream& operator<<(ostream &os, const scientific_type<T> &w) {
    format_guard _{os};
    os << scientific << uppercase << showpos;
    return os << w.value;
}

int main()
{
    {
        format_guard _;
        cout << hex << scientific << showbase << uppercase;

        cout << "Numbers with special formatting:\n";
        cout << 0x123abc << '\n';
        cout << 0.123456789 << '\n';
    }

    cout << "Same numbers, but normal formatting again:\n";
    cout << 0x123abc << '\n';
    cout << 0.123456789 << '\n';

    cout << "Mixed formatting: "
         << 123.0 << " "
         << scientific_type{123.0} << " "
         << 123.456 << '\n';

}
