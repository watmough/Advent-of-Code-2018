// Advent of Code 2018
// Day 12 - Subterranean Sustainability

#include "aoc.hpp"
using namespace std;

int main()
{
    // read input
    auto input{read_input("day_12.txt")};

    // read initial state
    string state = string("...") + input.front().substr(string("initial state: ").length()) + string("...");
    auto prevtotal{0}, offset{3};
    for (auto gen = 1ll; gen < 50000000000; ++gen)
    {
        string prime{state};
        for (auto pos = 0; pos < state.length() - 4; ++pos)
        {
            // check rules for this
            for (auto r{begin(input) + 2}; r != end(input); ++r)
            {
                // apply rule to find any matches, comparing first 5 characters of rule
                if (state.compare(pos, 5, *r, 0, 5) == 0)
                {
                    // match, copy char 10 of rule to offset 2 from pos
                    prime[pos + 2] = (*r)[9];
                    break;
                }
            }
        }
        state = string("..") + prime + string(".."), offset += 2;
        int total{0};
        for (auto pos{0}; pos < state.length(); ++pos)
            total += (state[pos] == '#' ? pos - offset : 0);
        if (gen == 20) {
            cout << "Part 1: Total is " << total << "\n";
        }
        if (gen == 125) {
            cout << "Part 2: Total is " << total + (50'000'000'000 - gen) * (total - prevtotal) << "\n";
            break;
        };
        prevtotal = total;
    }
}
