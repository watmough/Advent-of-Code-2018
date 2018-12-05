// Advent of Code 2018
// Day 01 - Chronal Calibration

#include "../aoc.hpp"
using namespace std;

int main() 
{
    // read input
    auto changes = read_ints("day_01.txt");

    // Part 1 - calculate final frequency
    cout << "Part 1: " << accumulate(begin(changes),end(changes),0l) << endl;

    // Part 2 - change frequencies until we see a duplicate frequency
    //          freq needs to be reset so we catch first repeated freq
    auto freq{0l};
    auto part2complete{false};
    auto freqs{unordered_set<int64_t>()};
    while (!part2complete) {
        transform(begin(changes),end(changes),inserter(freqs,begin(freqs)),
                    [&](const int64_t& c) -> int64_t {
                        if (freqs.count((freq+=c))>0 && !part2complete) 
                            cout << "Part 2: " << freq << "\n", part2complete = true;
                        return freq;
                    });
    }
}
