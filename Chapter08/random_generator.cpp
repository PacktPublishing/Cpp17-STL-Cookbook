#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <algorithm>

using namespace std;

template <typename RD>
void histogram(size_t partitions, size_t samples)
{
    partitions = max<size_t>(partitions, 10);

    using rand_t = typename RD::result_type;

    RD rd;
    rand_t div ((double(RD::max()) + 1) / partitions);

    vector<size_t> v (partitions);

    for (size_t i {0}; i < samples; ++i) {
        ++v[rd() / div];
    }

    rand_t max_elm (*max_element(begin(v), end(v)));
    rand_t max_div (max(max_elm / 100, rand_t(1)));
    for (size_t i {0}; i < partitions; ++i) {
        cout << setw(2) << i << ": "
             << string(v[i] / max_div, '*') << '\n';
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <partitions> <samples>\n";
        return 1;
    }

    size_t partitions {stoull(argv[1])};
    size_t samples    {stoull(argv[2])};

    cout << "random_device" << '\n';
    histogram<random_device>(partitions, samples);

    cout << "\ndefault_random_engine" << '\n';
    histogram<default_random_engine>(partitions, samples);

    cout << "\nminstd_rand0" << '\n';
    histogram<minstd_rand0>(partitions, samples);
    cout << "\nminstd_rand" << '\n';
    histogram<minstd_rand>(partitions, samples);

    cout << "\nmt19937" << '\n';
    histogram<mt19937>(partitions, samples);
    cout << "\nmt19937_64" << '\n';
    histogram<mt19937_64>(partitions, samples);

    cout << "\nranlux24_base" << '\n';
    histogram<ranlux24_base>(partitions, samples);
    cout << "\nranlux48_base" << '\n';
    histogram<ranlux48_base>(partitions, samples);

    cout << "\nranlux24" << '\n';
    histogram<ranlux24>(partitions, samples);
    cout << "\nranlux48" << '\n';
    histogram<ranlux48>(partitions, samples);

    cout << "\nknuth_b" << '\n';
    histogram<knuth_b>(partitions, samples);
}
