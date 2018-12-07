// Advent of Code 2018
// Day 07 - 

#include "aoc.hpp"
using namespace std;

#if 1
    #define FILENAME "day_07.txt"
    #define COUNT 101
#else
    #define FILENAME "day_07_tst.txt"
    #define COUNT 7
#endif

set<char> available(set<char> chars, multimap<char,char> has_dep)
{
    for (auto dep:has_dep) {
        cout << dep.first << " has dep of " << dep.second << "\n";
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

// set<char> recurse_deps(char c,map<char,char> has_dep)
// {
//     set<char> deps;


// }

// map<char,char> get_transitive_deps(set<char> chars,map<char,char> has_dep)
// {
//     // add in transitive deps
//     for (auto c:chars) {
//         auto deps = recurse_deps(c,has_dep);
//         for (auto cd:deps) {
//             has_dep.push_back(make_pair(c,cd));
//         }
//     }
//     return has_dep;
// }

int main()
{
    auto chars = set<char>{};
    auto has_dep = multimap<char,char>{};

    // Step T must be finished before step W can begin.
    // read data
    FILE *f = fopen(FILENAME,"rb");
    char fs,ss;
    while (!feof(f) && fscanf(f,"Step %c must be finished before step %c can begin.\n",&fs,&ss)) {
        printf("%c -> %c\n",fs,ss);
        chars.insert(fs);
        chars.insert(ss);
        has_dep.insert(make_pair(ss,fs));
    }
    fclose(f);

    // transitive deps
//    has_dep = get_transitive_deps(chars,has_dep);

    auto order = string{""};

    // for each step,
    while (chars.size()>0) {
        // candidates w/ no dependencies
        auto candidates = available(chars,has_dep);

        // do first only
        auto c = *(begin(candidates));
        order.push_back(c);

        // clean up dependencies
        has_dep = done_step(c, has_dep);
        chars.erase(c);

        // print order so far
        cout << order << "\n";
    }

    printf("Part 1: ...: \n");

    printf("Part 2: ...: \n");
    return 0;
}

