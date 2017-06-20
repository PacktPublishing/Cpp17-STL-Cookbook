#include <iostream>
#include <iomanip>
#include <locale>

using namespace std;

void print_aligned_demo(int val, size_t width, char fill_char = ' ') {

    cout << "================\n";
    cout << setfill(fill_char);
    cout << left     << setw(width) << val << '\n';
    cout << right    << setw(width) << val << '\n';
    cout << internal << setw(width) << val << '\n';
}

int main()
{
    print_aligned_demo(123456, 15);
    print_aligned_demo(123456, 15, '_');

    cout << hex << showbase;
    print_aligned_demo(0x123abc, 15);

    cout << oct;
    print_aligned_demo(0123456, 15);

    cout << "A hex number with upper case letters: "
         << hex << uppercase << 0x123abc << '\n';

    cout << "A number: " << 100 << '\n';
    cout << dec;

    cout << "Oops. now in decimal again: " << 100 << '\n';

    cout << "true/false values: "
         << true << ", " << false << '\n';
    cout << boolalpha
         << "true/false values: "
         << true << ", " << false << '\n';

    cout << "doubles: "
         << 12.3 << ", "
         << 12.0 << ", "
         << showpoint << 12.0 << '\n';

    cout << "scientific double: " << scientific << 123000000000.123 << '\n';
    cout << 100.0 << '\n';
    cout << "fixed      double: " << fixed      << 123000000000.123 << '\n';

    cout << "Very precise double: " << setprecision(10) << 0.0000000001 << '\n';
    cout << "Less precise double: " << setprecision(1) << 0.0000000001 << '\n';
}
