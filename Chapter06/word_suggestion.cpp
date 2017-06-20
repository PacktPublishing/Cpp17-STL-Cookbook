#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template <typename T>
class trie
{
    map<T, trie> tries;

public:
    template <typename It>
    void insert(It it, It end_it) {
        if (it == end_it) { return; }
        tries[*it].insert(next(it), end_it);
    }

    template <typename C>
    void insert(const C &container) {
        insert(begin(container), end(container));
    }

    void insert(const initializer_list<T> &il) {
        insert(begin(il), end(il));
    }

    void print(list<T> &l) const {
        if (tries.empty()) {
            copy(begin(l), end(l), ostream_iterator<T>{cout, " "});
            cout << '\n';
        }
        for (const auto &p : tries) {
            l.push_back(p.first);
            p.second.print(l);
            l.pop_back();
        }
    }

    void print() const {
        list<T> l;
        print(l);
    }

    template <typename It>
    optional<reference_wrapper<const trie>> subtrie(It it, It end_it) const {
        if (it == end_it) { return ref(*this); }

        auto found (tries.find(*it));
        if (found == end(tries)) { return {}; }

        return found->second.subtrie(next(it), end_it);
    }

    template <typename C>
    auto subtrie(const C &c) const { return subtrie(begin(c), end(c)); }
};


static void prompt()
{
    cout << "Next input please:\n > ";
}

int main()
{
    trie<string> t;

    fstream infile {"db.txt"};
    for (string line; getline(infile, line);) {
        istringstream iss {move(line)};
        t.insert(istream_iterator<string>{iss}, {});
    }


    prompt();
    for (string line; getline(cin, line);) {
        istringstream iss {move(line)};

        if (auto st (t.subtrie(istream_iterator<string>{iss}, {})); st) {
            cout << "Suggestions:\n";
            st->get().print();
        } else {
            cout << "No suggestions found.\n";
        }
        cout << "----------------\n";
        prompt();
    }
}

