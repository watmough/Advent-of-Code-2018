// Advent of Code 2018
//
// Day 01 - Chronal Calibration

// Jonathans-iMac:Advent-of-Code-2018 jonathan$ ./day_01
// Part 1: Total: 472
// Part 2: First Duplicate: 66932
// Jonathans-iMac:Advent-of-Code-2018 jonathan$

// Notes on performance: 
// - using unordered_set
// - using find(it,it,val) vs. unordered_set.find(val)!=end(values)
//
// Jonathans-iMac:Advent-of-Code-2018 jonathan$ ./day_01
// Part 1: Total: 472
// Part 1: Elapsed: 0.000666105
// Part 2: First Duplicate: 66932
// Part 2: Elapsed: 29.1529
//
// Jonathans-iMac:Advent-of-Code-2018 jonathan$ ./day_01
// Part 1: Total: 472
// Part 1: Elapsed: 0.000145164
// Part 2: First Duplicate: 66932
// Part 2: Elapsed: 0.0179688
// Jonathans-iMac:Advent-of-Code-2018 jonathan$

#include "aoc.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    auto input = vector<string>(read_input("day_01.txt"));

    auto starttime = chrono::high_resolution_clock::now();
    auto total = int64_t{0};
    auto values = unordered_set<int64_t>();                                         // 2x faster approc than set
    auto firstloop = true;
    auto found = false;

    while (!found) {
        for (auto l : input) {
            total += stoi(l);
//            if (!found && find(begin(values),end(values),total)!=end(values)) {   // 1000x slower !!
            if (!found && values.find(total)!=end(values)) {                        // equiv to using count(total)>0
                cout << "Part 2: First Duplicate: " << total << endl;
                cout << "Part 2: Elapsed: " << chrono::duration<double>(chrono::high_resolution_clock::now()-starttime).count() << endl;
                found = true;
            }
            values.insert(total);
        }
        if (firstloop) {
            cout << "Part 1: Total: " << total << endl;
            cout << "Part 1: Elapsed: " << chrono::duration<double>(chrono::high_resolution_clock::now()-starttime).count() << endl;
            firstloop = false;
        }
    }
}