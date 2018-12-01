# Advent-of-Code-2018

### Day 1 - [Chronal Calibration](https://adventofcode.com/2018/day/1)

Rank: 894 / 797

Identify the selected frequency, then the first repeated frequency if all the changes are
repeatedly re-applied as needed.

```C++
// Advent of Code 2018
// Day 01 - Chronal Calibration

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#include "../reader.hpp"

using namespace std;

int main() 
{
    // read in the input
    ifstream ifs("day_01.txt",ifstream::in);    
    auto lines = vector<string>(read_input(ifs));

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
                    [&](int64_t v) -> int64_t 
                    {
                        freq+=v;
                        if (freqs.count(freq)>0) {
                            cout << "Part 2: " << freq << "\n";
                            exit(0);
                        }
                        return freq;
                    });
    }
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time AlternateSolutions/day_01
Part 1: 472
Part 2: 66932

real    0m0.031s
user    0m0.027s
sys     0m0.003s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```
