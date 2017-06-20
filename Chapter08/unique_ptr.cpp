#include <iostream>
#include <memory>

using namespace std;

class Foo
{
public:
    string name;

    Foo(string n)
        : name{move(n)}
    { cout << "CTOR " << name << '\n'; }

    ~Foo() { cout << "DTOR " << name << '\n'; }
};

void process_item(unique_ptr<Foo> p)
{
    if (!p) { return; }

    cout << "Processing " << p->name << '\n';
}

int main()
{
    {
        unique_ptr<Foo> p1 {new Foo{"foo"}};
        auto            p2 (make_unique<Foo>("bar"));
    }

    process_item(make_unique<Foo>("foo1"));

    auto p1 (make_unique<Foo>("foo2"));
    auto p2 (make_unique<Foo>("foo3"));

    process_item(move(p1));

    cout << "End of main()\n";
}
