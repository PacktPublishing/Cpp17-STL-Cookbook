#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>

using namespace std;

static bool odd(int n) { return n % 2; }

int main()
{
    // Note that, as the recipe in the book says, this algorithm
    // is not supposed to be a solution of some problem.
    // This example program is rather about demonstrating how to
    // use the new execution policies in order to use the new
    // parallel versions of existing STL algorithms.

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
