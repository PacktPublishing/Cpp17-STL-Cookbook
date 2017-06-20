#include <iostream>
#include <iomanip>
#include <tuple>
#include <functional>
#include <string>
#include <list>

using namespace std;

static void print_student(size_t id, const string &name, double gpa)
{
    cout << "Student " << quoted(name) << ", ID: "
         << id << ", GPA: " << gpa << '\n';
}

int main()
{
    using student = tuple<size_t, string, double>;
    student john {123, "John Doe"s, 3.7};

    {
        const auto &[id, name, gpa] = john;
        print_student(id, name, gpa);
    }
    cout << "-----\n";

    auto arguments_for_later = {
        make_tuple(234, "John Doe"s, 3.7),
        make_tuple(345, "Billy Foo"s, 4.0),
        make_tuple(456, "Cathy Bar"s, 3.5),
    };

    for (const auto &[id, name, gpa] : arguments_for_later) {
        print_student(id, name, gpa);
    }
    cout << "-----\n";

    apply(print_student, john);
    cout << "-----\n";

    for (const auto &args : arguments_for_later) {
        apply(print_student, args);
    }
    cout << "-----\n";
}
