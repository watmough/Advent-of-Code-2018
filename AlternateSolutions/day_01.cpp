// Advent of Code 2018
// Day 01 - Chronal Calibration

#include "../aoc.hpp"
using namespace std;

int main() 
{
    // read input
    auto lines = vector<string>(read_input("day_01.txt"));

    // Part 1 - parse input lines to numbers and total
    auto freq = int64_t(0);
    auto values = vector<int64_t>();
    transform(begin(lines),end(lines),back_inserter(values),
              [&](string s) -> int64_t {int64_t val=stoi(s); freq+=val; return val;});
    cout << "Part 1: " << freq << endl;

    // Part 2 - change frequencies until we see a duplicate frequency
    //          freq needs to be reset so we catch first repeated freq
    freq = 0;
    auto freqs = set<int64_t>();
    while (true) {
        transform(begin(values),end(values),inserter(freqs,end(freqs)),
                    [&](int64_t v) -> int64_t {
                        if (freqs.count((freq+=v))>0) {
                            cout << "Part 2: " << freq << "\n";
                            exit(0);
                        }
                        return freq;
                    });
    }
}

