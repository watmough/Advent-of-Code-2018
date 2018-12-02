# Advent-of-Code-2018

### Day 2 - [Inventory Management System](https://adventofcode.com/2018/day/2)

Rank: 1086 / 1029

Compute a checksum over a list of box ids, then identify two box ids differing by only
a single letter.

### Improved Solution

```C++
// Advent of Code 2018
//
// Day 02 - Inventory Management System

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include "../reader.hpp"
#include "../utils.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    auto input = vector<string>(read_input("day_02.txt"));

    // Part 1 - Compute a checksum from multiplying counts of words with letters occurring exactly 2 or 3 times
    auto twos{0}, threes{0};
    for_each(begin(input),end(input),
        [&](auto& w) { 
            any_of(begin(w),end(w),[&](auto& c)->bool {return count(begin(w),end(w),c)==2;}) && twos++;
            any_of(begin(w),end(w),[&](auto& c)->bool {return count(begin(w),end(w),c)==3;}) && threes++;
        });
    cout << "Part 1: Checksum: " << twos*threes << "\n";

    // Part 2 - find the two strings that differ by only a single letter
    for_each(begin(input),end(input),
        [&](auto& w1) {
            any_of(begin(input),end(input),[&](auto& w2)->bool {
                if (count_mismatches(begin(w1),end(w1),begin(w2))==1)
                    cout << "Part 2: Single letter diff: "<< w1 << " " << w2 << "\n";
                return false;        // yes, no short-circuit out, and we print the result twice
            });
        });
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./AlternateSolutions/day_02
Part 1: Checksum: 5658
Part 2: Single letter diff: ndmgyjkpruszlbaqwficavxneo nomgyjkpruszlbaqwficavxneo
Part 2: Single letter diff: nomgyjkpruszlbaqwficavxneo ndmgyjkpruszlbaqwficavxneo

real    0m0.003s
user    0m0.002s
sys     0m0.001s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

### Original Solution

```C++
// Advent of Code 2018
//
// Day 02 - Inventory Management System

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>
#include "reader.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream ifs("day_02.txt",ifstream::in);
    vector<string> input = read_input(ifs);

    // Part 1: count 2 of any letter, and 3 of any letter and compute checksum
    auto twos = 0;
    auto threes = 0;
    for (auto l : input) {
        // get unique letters
        auto u = set<char>();
        auto twofound = false;
        auto threefound = false;
        copy(begin(l),end(l),inserter(u,begin(u)));
        for (auto c : u) {
            if (!twofound && count(begin(l),end(l),c)==2) twofound=true;
            if (!threefound && count(begin(l),end(l),c)==3) threefound=true;
        }
        twofound && twos++;
        threefound && threes++;
    }
    cout << "Part 1: Checksum: " << twos*threes << "\n";

    // Part 2 - find the two strings that differ by only a single letter
    for (auto l : input) {
        for (auto m : input) {
            // count differing letters
            auto d = 0;
            auto it1 = begin(l);
            auto it2 = begin(m);
            for (;it1!=end(l);++it1,++it2) {
                if (*it1!=*it2) d++;
            }
            if (d==1) {
                cout << "Part 2: Boxes: " << l << " and " << m << "\n";
                exit(0);
            }
        }
    }
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_02
Part 1: Checksum: 5658
Part 2: Boxes: ndmgyjkpruszlbaqwficavxneo and nomgyjkpruszlbaqwficavxneo

real    0m0.008s
user    0m0.006s
sys     0m0.001s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

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
