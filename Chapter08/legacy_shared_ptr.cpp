#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Foo
{
    string name;

    Foo(string n)
        : name{n}
    { cout << "CTOR " << name << '\n'; }

    ~Foo() { cout << "DTOR " << name << '\n';}

public:
    static Foo* create_foo(string s) { return new Foo{move(s)}; }

    static void destroy_foo(Foo *p) { delete p; }
};

static shared_ptr<Foo> make_shared_foo(string s)
{
    return {Foo::create_foo(move(s)), Foo::destroy_foo};
}

static unique_ptr<Foo, void (*)(Foo*)> make_unique_foo(string s)
{
    return {Foo::create_foo(move(s)), Foo::destroy_foo};
}

int main()
{
    auto ps (make_shared_foo("shared Foo instance"));

    auto pu (make_unique_foo("unique Foo instance"));
}
