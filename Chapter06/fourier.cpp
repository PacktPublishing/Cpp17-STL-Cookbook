#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <valarray>
#include <cmath>

using namespace std;

using cmplx = complex<double>;
using csignal = vector<cmplx>;

class num_iterator {
    size_t i;
public:

    explicit num_iterator(size_t position) : i{position} {}

    size_t operator*() const { return i; }

    num_iterator& operator++() {
        ++i;
        return *this;
    }

    bool operator!=(const num_iterator &other) const {
        return i != other.i;
    }
};

#if 0
csignal fourier_transform(const csignal &s, bool back = false)
{
    csignal t(s.size());

    const double pol {2.0 * M_PI * (back ? -1.0 : 1.0)};
    const double div {back ? 1.0 : double(s.size())};

    for (size_t k {0}; k < t.size(); ++k) {
        for (size_t j {0}; j < s.size(); ++j) {
            t[k] += s[j] * polar(1.0, pol * k * j / double(s.size()));
        }
        t[k] /= div;
    }

    return t;
}
#else

csignal fourier_transform(const csignal &s, bool back = false)
{
    csignal t (s.size());

    const double pol {2.0 * M_PI * (back ? -1.0 : 1.0) / s.size()};
    const double div {back ? 1.0 : double(s.size())};

    auto sum_up ([=, &s] (size_t j) {
        return [=, &s] (cmplx c, size_t k) {
            return c + s[k] * polar(1.0, pol * k * j);
        };
    });

    auto to_ft ([=, &s](size_t j){
        return accumulate(num_iterator{0}, num_iterator{s.size()}, cmplx{},
            sum_up(j)) / div;
    });

    transform(num_iterator{0}, num_iterator{s.size()}, begin(t), to_ft);

    return t;
}

#endif

static auto gen_cosine (size_t period_len)
{
    return [period_len, n{0}] () mutable {
        return cos(double(n++) * 2.0 * M_PI / period_len);
    };
}

static auto gen_square_wave (size_t period_len)
{
    return [period_len, n{period_len*7/4}] () mutable {
        return ((n++ * 2 / period_len) % 2) * 2 - 1.0;
    };
}

template <typename F>
static csignal signal_from_generator(size_t len, F gen)
{
    csignal r (len);
    generate(begin(r), end(r), gen);
    return r;
}

static void print_signal (const csignal &s)
{
    auto real_val ([](cmplx c) { return c.real(); });
    transform(begin(s), end(s), ostream_iterator<double>{cout, " "}, real_val);
    cout << '\n';
}

int main()
{
    const size_t sig_len {100};

    auto cosine      (signal_from_generator(sig_len, gen_cosine(sig_len / 2)));
    auto square_wave (signal_from_generator(sig_len, gen_square_wave(sig_len / 2)));

    auto trans_sqw (fourier_transform(square_wave));

    fill(next(begin(trans_sqw), 10), prev(end(trans_sqw), 10), 0);
    auto mid (fourier_transform(trans_sqw, true));

    print_signal(cosine);
    print_signal(fourier_transform(cosine));

    print_signal(mid);
    print_signal(trans_sqw);

    print_signal(square_wave);
    print_signal(fourier_transform(square_wave));
}
