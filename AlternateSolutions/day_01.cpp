// Advent of Code 2018
// Day 01 - Chronal Calibration

#include "../aoc.hpp"
using namespace std;

int main() 
{
    // read input
    auto lines = vector<string>(read_input("day_01.txt"));

    // Part 1 - parse input lines to numbers and total
    auto vals = vector<int>();
    transform(begin(lines),end(lines),back_inserter(vals),[&](string s){return stoi(s);});
    auto freq = accumulate(begin(vals),end(vals),0);
    cout << "Part 1: " << freq << endl;

    // stateful closure which returns true when passed value has been seen before
    struct seen_before : public std::unary_function<int,bool> {
        bool operator() (const int& f) {
            if (seen.count(f)>0)
                return true;
            seen.insert(f);
            return false;
        };
        set<int> seen;
    };

    // Part 2 - Change frequencies until 
    cycle_until(begin(vals),end(vals),[&](auto& v) {
        return seen_before((freq+=v));
    });

    // // Part 2 - change frequencies until we see a duplicate frequency
    // //          freq needs to be reset so we catch first repeated freq
    // freq = 0;
    // auto freqs = set<int64_t>();
    // while (true) {
    //     transform(begin(vals),end(vals),inserter(freqs,end(freqs)),
    //                 [&](int64_t v) -> int64_t {
    //                     if (freqs.count((freq+=v))>0) {
    //                         cout << "Part 2: " << freq << "\n";
    //                         exit(0);
    //                     }
    //                     return freq;
    //                 });
    // }
}

