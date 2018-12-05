// Advent of Code 2018
// Day 05 - 

#include "aoc.hpp"
using namespace std;

struct is_delim : std::unary_function<const char&, bool> {
    bool operator()(const char& c) const { return strchr(" |*%^",int(c))!=nullptr; }
};

int main(int argc, char* argv[])
{
    auto input = read_input("day_05.txt");

    for (auto l : input) {

        auto tokens = split(begin(l),end(l),is_delim());
        cout << l << " -> ";
        for (auto t : tokens)
            cout << t << " ";
        cout << "\n";
    }
}