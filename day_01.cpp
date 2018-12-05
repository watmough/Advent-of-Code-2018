// Advent of Code 2018
// Day 01 - Chronal Calibration

#include "aoc.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    auto input = read_ints("day_01.txt");

    auto total{0};
    auto values{unordered_set<int>()};
    auto part1complete{false}, part2complete{false};

    while (!part2complete) {
        for (const auto& s : input) {
            total += s;
            if (values.find(total)!=end(values) && !part2complete)
                cout << "Part 2: First Duplicate: " << total << endl, part2complete=true;
            values.insert(total);
        }
        if (!part1complete)
            cout << "Part 1: Total: " << total << endl, part1complete=true;
    }
}
