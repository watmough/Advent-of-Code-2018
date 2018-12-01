// Advent of Code 2018
//
// Day 01 - Chronal Calibration

// Jonathans-iMac:Advent-of-Code-2018 jonathan$ ./day_01
// Part 1: Total: 472
// Part 2: First Duplicate: 66932
// Jonathans-iMac:Advent-of-Code-2018 jonathan$

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include "reader.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream ifs("day_01.txt",ifstream::in);
    vector<string> input = read_input(ifs);

    auto total = int64_t{0};
    auto values = set<int64_t>();
    auto firstloop = true;
    auto found = false;

    while (!found) {
        for (auto l : input) {
            total += stoi(l);
            if (!found && values.count(total)>0) {
                cout << "Part 2: First Duplicate: " << total << endl;
                found = true;
            }
            values.insert(total);
        }
        if (firstloop) {
            cout << "Part 1: Total: " << total << endl;
            firstloop = false;
        }
    }
}