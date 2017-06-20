#include <iostream>
#include <variant>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

class cat {
    string name;

public:
    cat(string n) : name{n} {}

    void meow() const {
        cout << name << " says Meow!\n";
    }
};

class dog {
    string name;

public:
    dog(string n) : name{n} {}

    void woof() const {
        cout << name << " says Woof!\n";
    }
};

using animal = variant<dog, cat>;

template <typename T>
bool is_type(const animal &a) {
    return holds_alternative<T>(a);
}

struct animal_voice
{
    void operator()(const dog &d) const { d.woof(); }
    void operator()(const cat &c) const { c.meow(); }
};

int main()
{
    list<animal> l {cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"}};

    for (const animal &a : l) {
        switch (a.index()) {
        case 0:
            get<dog>(a).woof();
            break;
        case 1:
            get<cat>(a).meow();
            break;
        }
    }
    cout << "-----\n";

    for (const animal &a : l) {
        if (const auto d (get_if<dog>(&a)); d) {
            d->woof();
        } else if (const auto c (get_if<cat>(&a)); c) {
            c->meow();
        }
    }
    cout << "-----\n";

    for (const animal &a : l) {
        visit(animal_voice{}, a);
    }
    cout << "-----\n";

    cout << "There are "
         << count_if(begin(l), end(l), is_type<cat>)
         << " cats and "
         << count_if(begin(l), end(l), is_type<dog>)
         << " dogs in the list.\n";
}

