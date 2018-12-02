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