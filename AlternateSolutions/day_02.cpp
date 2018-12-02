// Advent of Code 2018
// Day 02 - Inventory Management System

#include "../aoc.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    auto input = vector<string>(read_input("day_02.txt"));

    // Part 1 - Compute a checksum from multiplying counts of words with letters occurring exactly 2 or 3 times
    auto twos{0}, threes{0};
    for_each(begin(input),end(input),[&](auto& w) { 
        any_of(begin(w),end(w),[&](auto& c)->bool {return count(begin(w),end(w),c)==2;}) && twos++;
        any_of(begin(w),end(w),[&](auto& c)->bool {return count(begin(w),end(w),c)==3;}) && threes++;
    });
    cout << "Part 1: Checksum: " << twos*threes << "\n";

    // Part 2 - find the two strings that differ by only a single letter
    for_all_pairs(begin(input),end(input),[&](auto& w1, auto& w2) {
        auto found = bool(count_mismatches(begin(w1),end(w1),begin(w2))==1);
        found && cout << "Part 2: Single letter diff: "<< w1 << " " << w2 << "\n";
    });
}
