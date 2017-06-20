#include <iostream>
#include <cstdio>
#include <map>
#include <string>

template <typename T>
void print_charcount_cpp11(const T &map, char c)
{
    const auto itr (map.find(c));
    if (itr != map.end()) {
        // *itr is valid. Do something with it.
        std::cout << "There are " << itr->second << " " << c << " characters." << "\n";
    } else {
        // itr is invalid, must not be accessed, but is available
        std::cout << "There are " << 0 << " " << c << " characters." << "\n";
    }
    // itr is not necessarily safe to dereference, but still available
}

template <typename T>
void print_charcount_cpp17(const T &map, char c)
{
    if (const auto itr (map.find(c)); itr != map.end()) {
        std::cout << "There are " << itr->second << " " << c << " characters." << "\n";
    } else {
        std::cout << "There are " << 0 << " " << c << " characters." << "\n";
    }
    // itr is not visible here
}

int main()
{
    {
        std::map<char, size_t> character_map {{'a', 10}, {'b', 20} /* , ... */};
        print_charcount_cpp11(character_map, 'a');
        print_charcount_cpp11(character_map, 'c');

        print_charcount_cpp17(character_map, 'a');
        print_charcount_cpp17(character_map, 'c');
    }

    {
        std::cout << "Please enter a character: ";
        switch (char c (getchar()); c) {
        case 'a' ... 'z':
            std::cout << "You entered a lower case letter: " << c << "\n";
            break;
        case 'A' ... 'Z':
            std::cout << "You entered an upper case letter: " << c << "\n";
            break;
        default:
            std::cout << "You entered something else: " << c << "\n";
        }
    }
}


