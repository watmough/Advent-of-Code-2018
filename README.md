# Advent-of-Code-2018

### Day 5 - [Alchemical Reduction](https://adventofcode.com/2018/day/5)

Rank: 2488 / 2635

```C++
// Advent of Code 2018
// Day 05 - Alchemical Reduction

#include "aoc.hpp"
using namespace std;

// React a polymer by reducing adjacent units
// E.g. assert(react(string("dabAcCaCBAcCcaDA"))==string("dabCBAcaDA")); 
string react(const string& s)
{
    auto sp = string(begin(s),begin(s)+1);
    for (auto c=begin(s)+1;c!=end(s);++c )
        if ((*c^sp.back())==('a'^'A')) sp.pop_back(); else sp.push_back(*c);
    return sp;
}

int main(int argc, char* argv[])
{
    // Part 1
    auto text{read_input("day_05.txt").front()};
    cout << "Part 1: Polymer length: " << react(text).length() << "\n";

    // Part 2 - Find shortest with 1 unit removed
    auto shortest{text.length()};
    for (auto u{'a'};u<='z';++u) {
        auto textpp{text};
        textpp.erase(std::remove(textpp.begin(), textpp.end(), u), textpp.end());
        textpp.erase(std::remove(textpp.begin(), textpp.end(), toupper(u)), textpp.end());
        shortest = min(shortest,react(textpp).length());
    }
    cout << "Part 2: Shortest polymer: " << shortest << "\n";
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_05
Part 1: Polymer length: 10804
Part 2: Shortest polymer: 6650

real    0m0.013s
user    0m0.012s
sys     0m0.001s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

### Alternate Solution in C

```C
// Advent of Code 2018
// Day 05 - Alchemical Reduction

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int react(char * s) {
    char *r = s+1, *w = s;
    while (*r)
        if ((*r^*w)==('A'^'a')) w--, r++; else *++w=*r++;
    *++w='\0';
    return w-s;
}

int main()
{
#if 1
    #include "day_05.h"
#else
    char o[] = "dabAcCaCBAcCcaDA";
    char s[] = "dabAcCaCBAcCcaDA";
#endif

    int l = react(s);
    printf("Part 1: Length: %d\n",l);

    int b = l;
    for (int i='a';i<='z';++i) {
        char *p=s,*q=o;
        while (*p)
            if (tolower(*p)==i) p++; else *q++=*p++;
        *q='\0';        
        int c = react(o);
        b = c<b ? c : b;
    }
    printf("Part 2: Best length: %d\n",b);
    return 0;
}
```

### Day 4 - [Repose Record](https://adventofcode.com/2018/day/4)

Rank: 1285 / 1394

Find the sleepiest guard's sleepiest minute, and the most habitually asleep guard on any minute.

```C++
// Advent of Code 2018
// Day 04 - Repose Record

#include "aoc.hpp"
using namespace std;

struct is_delim : std::unary_function<const char&, bool> {
    bool operator()(const char& c) const { return strchr(" :[]#-",int(c))!=nullptr; }
};

const static bool compare(const pair<int,int>& a, const pair<int,int>& b) {
    return (a.second<b.second);
}

int main(int argc, char* argv[])
{
    vector<string> input = read_input("day_04.txt");
    sort(begin(input),end(input));

    // build a map of guards to total sleep time and by minute asleep
    auto guard{0}, sleepat{59}, wakeat{0};
    auto sleeping = map<int,int>();
    auto minutes = map<int,array<int,60>>();
    for (auto l : input) {
        auto tokens = split(begin(l),end(l),is_delim());
        if (l.find("Guard")!=string::npos)  guard   = stoi(tokens[7]);
        if (l.find("asleep")!=string::npos) sleepat = stoi(tokens[5]);
        if (l.find("wake")) {
            wakeat = stoi(tokens[5]);
            sleeping[guard]+=wakeat-sleepat;
            for (int i=sleepat;i<wakeat;++i) minutes[guard][i]++;
        }
    }

    // Part 1 - Find the sleepiest guard * the minute he spent most asleep
    guard = max_element(begin(sleeping),end(sleeping),compare).operator*().first;
    auto minute = max_element(begin(minutes[guard]),end(minutes[guard]))-minutes[guard].data();
    cout << "Part 1: Guard * Minutes: " << guard*minute << "\n";

    // Part 2 - Find the Guard# * Most Slept in Minute
    auto maxminutes{0},mostminute{0},mostguard{0};
    for( auto g : minutes ) {
        // find the minute for this guard
        auto m = max_element(begin(minutes[g.first]),end(minutes[g.first]));
        auto minute = m-minutes[g.first].data();

        if (*m>maxminutes) {
            maxminutes = *m;
            mostminute = minute;
            mostguard = g.first;
        }
    }
    cout << "Part 2: Most frequently asleep guard * minute: " << mostguard << " m " << mostminute << " -> " << mostguard*mostminute << "\n";
}
```

### Day 3 - [No Matter How You Slice It](https://adventofcode.com/2018/day/3)

Rank: 2817/2449

Compute the total multiply claimed area of fabric. Identify the single claim that overlaps no other claims.

```C++
// Advent of Code 2018
// Day 03 - No Matter How You Slice It

#include "aoc.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> input = read_input("day_03.txt");

    // Part 1: Find the total area that overlaps between the claims
    vector<tuple<int,int,int,int,int>> claims;
    map<int,map<int,int>> dots;
    auto area_claimed = int{0};
    for (auto l : input) {
        auto tokens = split(l," #@,:x");
        claims.push_back(make_tuple(stoi(tokens[0]),stoi(tokens[1]),stoi(tokens[2]),
                                                    stoi(tokens[1])+stoi(tokens[3])-1,stoi(tokens[2])+stoi(tokens[4])-1));
        const auto& c = claims.back();
        for (int i=get<1>(c);i<=get<3>(c);++i) {
            for (int j=get<2>(c);j<=get<4>(c);++j) {
                dots[i][j]++;
                if (dots[i][j]==2)
                    area_claimed++;
            }
        }
    }
    cout << "Part 1: Overlapping area: " << area_claimed << "\n";

    // Part 2 - Find the one claim that does not overlap any others
    for (auto c : claims) {
        auto overlap = false;
        for (int i=get<1>(c);i<=get<3>(c);++i) {
            for (int j=get<2>(c);j<=get<4>(c);++j) {
                if (dots[i][j]!=1)
                    overlap=true;
            }
        }
        if (!overlap) {
            cout << "Part 2: Non-overlapping claim: " << get<0>(c) << "\n";
        }
    }
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_03
Part 1: Overlapping area: 113966
Part 2: Non-overlapping claim: 235

real    0m0.395s
user    0m0.386s
sys     0m0.008s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

### Day 2 - [Inventory Management System](https://adventofcode.com/2018/day/2)

Rank: 1086 / 1029

Compute a checksum over a list of box ids, then identify two box ids differing by only
a single letter.

### Improved Solution

```C++
// Advent of Code 2018
// Day 02 - Inventory Management System

#include "../aoc.hpp"
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
    any_of(begin(input),end(input),[&](auto& w1)->bool {
        return any_of(begin(input),end(input),[&](auto& w2)->bool {
                    auto found = bool(count_mismatches(begin(w1),end(w1),begin(w2))==1);
                    found && cout << "Part 2: Single letter diff: "<< w1 << " " << w2 << "\n";
                    return found;
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
// Day 02 - Inventory Management System

#include "aoc.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    auto input = vector<string>(read_input("day_02.txt"));

    // Part 1: count 2 of any letter, and 3 of any letter and compute checksum
    auto twos = 0;
    auto threes = 0;
    for (auto l : input) {
        auto twofound = false;
        auto threefound = false;
        auto u = set<char>(begin(l),end(l));    // iterate over unique letters
        for (auto c : u) {
            if (count(begin(l),end(l),c)==2) twofound=true;
            if (count(begin(l),end(l),c)==3) threefound=true;
        }
        twofound && twos++;
        threefound && threes++;
    }
    cout << "Part 1: Checksum: " << twos*threes << "\n";

    // Part 2 - find the two strings that differ by only a single letter
    for (auto l : input) {
        for (auto m : input) {
            // count differing letters between all words
            auto d = 0;
            auto it1 = begin(l);
            auto it2 = begin(m);
            for (;it1!=end(l);++it1,++it2)
                if (*it1!=*it2) d++;
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
