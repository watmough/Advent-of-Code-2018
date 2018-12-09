# Advent-of-Code-2018

### Day 09 - [Marble Mania](https://adventofcode.com/2018/day/9)

Rank: 5973 / 5795

```C++
// Advent of Code 2018
// Day 09 - Marble Mania

#include "aoc.hpp"
using namespace std;

template <typename Iter>
void print_board(int player, const Iter& first, const Iter& last, const Iter& pos) {
    cout << "[" << player << "] ";
    for (auto it=first;it!=last;++it)
        if (it==pos) cout << "(" << *it << ")";
        else         cout << " " << *it << " ";
    cout << "\n";
}

template <typename Tscore>
pair<int,Tscore> whatarethescoresgeorgedawes(map<int,Tscore> scores) {
    auto chickendinner{Tscore{}};
    auto winner{0};
    for (auto s : scores) {
        if (s.second>chickendinner) { chickendinner=s.second, winner=s.first; };
    }
    cout << "Winner: " << winner << " with " << chickendinner << "\n";
    return make_pair(winner,chickendinner);
}

template <typename Tscore>
pair<int,Tscore> play_game(int players, int marbles, std::string part="") {
    auto b{list<int>{0}};
    auto score{map<int,Tscore>{}};
    auto player{0};
    auto pos{b.begin()};
    for (auto marble=1;marble<=marbles;++marble, player=(player+1)%players) {
        if (marble%23!=0) {
            for (auto i{0};i<2;++i) { if (pos==end(b)) pos=begin(b); pos++; }
            pos=b.insert(pos,marble);
        } else {
            for (auto i{0};i<7;++i) { if (pos==begin(b)) pos=end(b); pos--; }
            score[player]+=marble+*pos;
            pos=b.erase(pos);
        }
        if (marbles<100)
            print_board(player+1,begin(b),end(b),pos);
    }
    cout << part;
    return whatarethescoresgeorgedawes(score);
}

// Puzzle input: 405 players; last marble is worth 71700 points
int main(int argc, char **argv)
{
    play_game<int>(9,25);
    play_game<int>(10,1618);
    play_game<int>(13,7999);
    play_game<int>(17,1104);
    play_game<int>(21,6111);
    play_game<int>(30,5807);
    play_game<uint64_t>(405,71700,string("Part 1: "));
    play_game<uint64_t>(405,71700*100,"Part 2: ");
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_09
[1]  0 (1)
[2]  0 (2) 1
[3]  0  2  1 (3)
[4]  0 (4) 2  1  3
[5]  0  4  2 (5) 1  3
[6]  0  4  2  5  1 (6) 3
[7]  0  4  2  5  1  6  3 (7)
[8]  0 (8) 4  2  5  1  6  3  7
[9]  0  8  4 (9) 2  5  1  6  3  7
[1]  0  8  4  9  2 (10) 5  1  6  3  7
[2]  0  8  4  9  2  10  5 (11) 1  6  3  7
[3]  0  8  4  9  2  10  5  11  1 (12) 6  3  7
[4]  0  8  4  9  2  10  5  11  1  12  6 (13) 3  7
[5]  0  8  4  9  2  10  5  11  1  12  6  13  3 (14) 7
[6]  0  8  4  9  2  10  5  11  1  12  6  13  3  14  7 (15)
[7]  0 (16) 8  4  9  2  10  5  11  1  12  6  13  3  14  7  15
[8]  0  16  8 (17) 4  9  2  10  5  11  1  12  6  13  3  14  7  15
[9]  0  16  8  17  4 (18) 9  2  10  5  11  1  12  6  13  3  14  7  15
[1]  0  16  8  17  4  18  9 (19) 2  10  5  11  1  12  6  13  3  14  7  15
[2]  0  16  8  17  4  18  9  19  2 (20) 10  5  11  1  12  6  13  3  14  7  15
[3]  0  16  8  17  4  18  9  19  2  20  10 (21) 5  11  1  12  6  13  3  14  7  15
[4]  0  16  8  17  4  18  9  19  2  20  10  21  5 (22) 11  1  12  6  13  3  14  7  15
[5]  0  16  8  17  4  18 (19) 2  20  10  21  5  22  11  1  12  6  13  3  14  7  15
[6]  0  16  8  17  4  18  19  2 (24) 20  10  21  5  22  11  1  12  6  13  3  14  7  15
[7]  0  16  8  17  4  18  19  2  24  20 (25) 10  21  5  22  11  1  12  6  13  3  14  7  15
Winner: 4 with 32
Winner: 9 with 8317
Winner: 11 with 146373
Winner: 15 with 2764
Winner: 4 with 54718
Winner: 19 with 37305
Part 1: Winner: 111 with 428690
Part 2: Winner: 272 with 3628143500

real    0m0.897s
user    0m0.811s
sys     0m0.078s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

### Day 8 - [Memory Maneuver](https://adventofcode.com/2018/day/8)

Rank: 4671 / 4470

```C++
// Advent of Code 2018
// Day 08 - Memory Maneuver

#include "aoc.hpp"
using namespace std;

int sum_meta()
{
    int c{},m{},total{};
    cin >> c >> m;
    while (c--) 
        total+=sum_meta();
    while (m--) {
        int v{}; cin >> v;
        total+=v;
    }
    return total;
}

int sum_nodes()
{
    int c{},m{},total{};
    vector<int> children;
    cin >> c >> m;
    while (c--)
        children.push_back(sum_nodes());
    while (m--) {
        int v{}; cin >> v;
        if (children.empty())
            total+=v;
        else if (v>0&&v-1<children.size())
            total+=children[v-1];
    }
    return total;
}

int main(int argc, char* argv[])
{
    if (argc<2) {
        cout << "Usage: " << argv[0] << " 1|2 < data.txt\n";
        exit(0);
    }
    if (atoi(argv[1])==1)
        cout << "Part 1: Metadata sum: " << sum_meta() << "\n";
    else
        cout << "Part 2: Nodes sum: " << sum_nodes() << "\n";
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_08 1 < day_08.txt
Part 1: Metadata sum: 35911

real    0m0.018s
user    0m0.016s
sys     0m0.001s
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_08 2 < day_08.txt
Part 2: Nodes sum: 17206

real    0m0.018s
user    0m0.016s
sys     0m0.001s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

### Day 7 - [The Sum of Its Parts](https://adventofcode.com/2018/day/7)

Rank: 3857 / 6996

```C++
// Advent of Code 2018
// Day 07 - The Sum of Its Parts

#include "aoc.hpp"
using namespace std;

#if 1
    #define FILENAME "day_07.txt"
    #define COUNT 101
    #define WORKERS 5
    #define TIME 61
#else
    #define FILENAME "day_07_tst.txt"
    #define COUNT 7
    #define WORKERS 2
    #define TIME 1
#endif

void load_input(set<char>& chars, multimap<char,char>& has_dep)
{
    // Sample data: Step T must be finished before step W can begin.
    FILE *f = fopen(FILENAME,"rb");
    char fs,ss;
    while (!feof(f) && fscanf(f,"Step %c must be finished before step %c can begin.\n",&fs,&ss)) {
        // printf("%c -> %c\n",fs,ss);
        chars.insert(fs);
        chars.insert(ss);
        has_dep.insert(make_pair(ss,fs));
    }
    fclose(f);
}

set<char> available(set<char> chars, multimap<char,char> has_dep)
{
    for (auto dep : has_dep) {
        // cout << dep.first << " has dep of " << dep.second << "\n";
        chars.erase(dep.first);
    }
    return chars;
}

multimap<char,char> done_step(char c, multimap<char,char> has_dep)
{
    multimap<char,char> new_deps;
    for (auto d : has_dep) {
        if (d.second!=c)
            new_deps.insert(d);
    }
    return new_deps;
}

// Part 1 - Calculate the required ordering of the steps given the constraints
void part1()
{
    auto chars = set<char>{};
    auto has_dep = multimap<char,char>{};
    load_input(chars,has_dep);

    auto order = string{""};
    while (chars.size()>0) {
        // candidates w/ no dependencies
        auto candidates = available(chars,has_dep);

        // do first only
        auto c = *(begin(candidates));
        order.push_back(c);

        // done a task, make more tasks available
        has_dep = done_step(c, has_dep);
        chars.erase(c);
    }

    cout << "Part 1: The required task ordering is: " << order << "\n";
}

// Simulate a work queue ... of Elves
class work_queue
{
public:
    work_queue(int workers) : tasks(), workers(workers), thetime{0} {};

    bool inflight(char c) {
        return any_of(begin(tasks),end(tasks),[&](const auto& t)->bool{return t.first==c;});
    }

    int gettime() {
        return thetime;
    };

    int tick() {    // tick to the soonest available job, returning the time (may be >1 job)
        assert(haswork());
        std::stable_sort(begin(tasks),end(tasks),[&](const auto& l,const auto& r){return l.second<r.second;});
        return (thetime=tasks.front().second);
    };

    vector<pair<char,int>> completed()
    {
        auto done = vector<pair<char,int>>{};
        copy_if(begin(tasks),end(tasks),std::back_inserter(done),[&](const auto& t)->bool{return t.second==thetime;});
        for_each(begin(done),end(done),[&](const auto& t){tasks.erase(tasks.begin());});
        return done;
    }

    bool haswork() {
        return !tasks.empty();
    }

    bool busy() {
        return tasks.size()==workers;
    };

    pair<char,int> work(char c) {           // assign and return task,eta for this job
        assert(!busy());                    // must have at least one elf free
        auto t = make_pair(c,thetime+/* 61 or 1 */TIME+c-'A');
        tasks.push_back(t);
        return t;
    };
private:
    vector<pair<char,int>> tasks;
    int workers;
    int thetime;
};

int part2()
{
    auto chars = set<char>{};
    auto has_dep = multimap<char,char>{};
    load_input(chars,has_dep);

    // create a work queue
    work_queue w(WORKERS);

    // get candidates for next worker
    auto candidates = available(chars,has_dep);

    // for each step,
    while (chars.size()>0) {
        
        // assign a worker
        while (candidates.size() && !w.busy()) {
            auto c = *(begin(candidates)); 
            if (!w.inflight(c))
                w.work(c);
            candidates.erase(c);
        }

        // if busy, clock the next job to completion
        if (w.busy() || candidates.size()==0) {
            // clock
            w.tick();

            // handle completed tasks
            auto done = w.completed();
            for (auto completed : done) {
                // cout << "Completed: " << completed.first << " at time: " << completed.second << "\n";

                // completed a task
                has_dep = done_step(completed.first, has_dep);
                chars.erase(completed.first);

                // refresh list of candidates 
                // ### No Clang warning for having an auto on the next line ###
                candidates = available(chars,has_dep);
            }
        }
    }
    printf("Part 2: Finished at time: %d\n",w.gettime());
    return 0;
}

int main()
{
    part1();
    part2();
    return 0;
}
```

### Performance

```
Jonathans-iMac:Advent-of-Code-2018 jonathan$ time ./day_07
Part 1: The required task ordering is: HPDTNXYLOCGEQSIMABZKRUWVFJ
Part 2: Finished at time: 908

real    0m0.005s
user    0m0.003s
sys     0m0.001s
Jonathans-iMac:Advent-of-Code-2018 jonathan$
```

### Day 6 - Coming Soon!

Rank: 10335 / 9745



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
