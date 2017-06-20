#include <iostream>

static auto multicall (auto ...functions)
{
    return [=](auto x) {
        (void)std::initializer_list<int>{
            ((void)functions(x), 0)...
        };
    };
}

static auto for_each (auto f, auto ...xs) {
    (void)std::initializer_list<int>{
        ((void)f(xs), 0)...
    };
}

static auto brace_print (char a, char b) {
    return [=] (auto x) {
        std::cout << a << x << b << ", ";
    };
}

int main()
{
    auto f  (brace_print('(', ')'));
    auto g  (brace_print('[', ']'));
    auto h  (brace_print('{', '}'));
    auto nl ([](auto) { std::cout << '\n'; });

    auto call_fgh (multicall(f, g, h, nl));

    for_each(call_fgh, 1, 2, 3, 4, 5);
}
