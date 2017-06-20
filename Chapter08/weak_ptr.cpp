#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

struct Foo {
    int value;

    Foo(int i) : value{i} {}
    ~Foo() { cout << "DTOR Foo " << value << '\n'; }
};

void weak_ptr_info(const weak_ptr<Foo> &p)
{
    cout << "---------" << boolalpha
         << "\nexpired:   " << p.expired()
         << "\nuse_count: " << p.use_count()
         << "\ncontent:   ";

    if (const auto sp (p.lock()); sp) {
        cout << sp->value << '\n';
    } else {
        cout << "<null>\n";
    }
}


int main()
{
    weak_ptr<Foo> weak_foo;

    weak_ptr_info(weak_foo);

    {
        auto shared_foo (make_shared<Foo>(1337));
        weak_foo = shared_foo;

        weak_ptr_info(weak_foo);
    }

    weak_ptr_info(weak_foo);
}
