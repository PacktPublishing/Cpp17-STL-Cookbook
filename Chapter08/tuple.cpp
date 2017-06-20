#include <iostream>
#include <tuple>
#include <list>
#include <utility>
#include <string>
#include <iterator>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename T, typename ... Ts>
void print_args(ostream &os, const T &v, const Ts &...vs)
{
    os << v;

    (void)initializer_list<int>{((os << ", " << vs), 0)...};
}

template <typename ... Ts>
ostream& operator<<(ostream &os, const tuple<Ts...> &t)
{
    auto print_to_os ([&os](const auto &...xs) {
        print_args(os, xs...);
    });

    os << "(";
    apply(print_to_os, t);
    return os << ")";
}

template <typename T>
tuple<double, double, double, double>
sum_min_max_avg(const T &range)
{
    auto min_max (minmax_element(begin(range), end(range)));
    auto sum     (accumulate(begin(range), end(range), 0.0));
    return {sum, *min_max.first, *min_max.second, sum / range.size()};
}

template <typename T1, typename T2>
static auto zip(const T1 &a, const T2 &b)
{
    auto z ([](auto ...xs) {
        return [xs...](auto ...ys) {
            return tuple_cat(make_tuple(xs, ys) ...);
        };
    });
    return apply(apply(z, a), b);
}

int main()
{
    auto student_desc (make_tuple("ID",   "Name",    "GPA"));
    auto student      (make_tuple(123456, "John Doe", 3.7));

    cout << student_desc << '\n'
         << student << '\n';

    cout << tuple_cat(student_desc, student) << '\n';

    auto zipped (zip(student_desc, student));
    cout << zipped << '\n';

    auto numbers = {0.0, 1.0, 2.0, 3.0, 4.0};
    cout << zip(
            make_tuple("Sum", "Minimum", "Maximum", "Average"),
            sum_min_max_avg(numbers))
         << '\n';
}
