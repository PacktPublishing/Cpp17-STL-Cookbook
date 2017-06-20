#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <algorith>
#include <execution_policy>

using namespace std;

static bool odd(int n) { return n % 2; }

int main()
{
    vector<int> d (500);

    mt19937 gen;
    uniform_int_distribution<int> dis(0, 100000);

    auto rand_num ([=] () mutable { return dis(gen); });

    generate(execution::par, begin(d), end(d), rand_num);

    sort(execution::par, begin(d), end(d));

    reverse(execution::par, begin(d), end(d));

    auto odds (count_if(execution::par, begin(d), end(d), odd));

    cout << (100.0 * odds / d.size()) << "% of the numbers are odd.\n";
}
