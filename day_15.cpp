// Advent of Code 2018
// Day 15 - Beverage Bandits

#include "aoc.hpp"
using namespace std;

struct is_delim : std::unary_function<const char&, bool> {
    bool operator()(const char& c) const { return strchr(" |*%^",int(c))!=nullptr; }
};

int main(int argc, char* argv[])
{
    auto input = read_input("template.txt");

    for (auto l : input) {

        auto tokens = split(begin(l),end(l),is_delim());
        cout << l << " -> ";
        for (auto t : tokens)
            cout << t << " ";
        cout << "\n";
    }

    // identify elvces
    // identify goblins
    // for all elves
    {
        // attack? - adjacent to llive target
        {
            // select target with lowest hit points
            // deal damage
        }
        // move? 
        {
            // identify goblins
            // identify open adjacent squares to goblins
            // find paths - nearest by floodfill
            // pick nearest
        }
    }

}