#include <iostream>
#include <memory>
#include <string>
#include <tuple>

using namespace std;

struct student {
    size_t id;
    string name;
    double gpa;

    student(size_t i, string n, double g)
        : id{i}, name{n}, gpa{g}
    {}
    ~student() { cout << "student destructor\n"; }
};

using student_tuple = tuple<size_t, string, double>;

int main()
{
    shared_ptr<string> shared_name;

    {
        auto stud (make_shared<student>(123, "John Doe", 4.0));

        shared_name = shared_ptr<string>{stud, &stud->name};

        cout << *shared_name << '\n';
    }

    cout << *shared_name << '\n';

    {
        auto stud (make_shared<student_tuple>(321, "Foo Barista", 3.5));

        shared_name = shared_ptr<string>(stud, &get<1>(*stud));

        cout << *shared_name << '\n';
    }

    cout << *shared_name << '\n';
}
