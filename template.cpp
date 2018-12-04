// Advent of Code 2018
// Day 0x - 

#include "aoc.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    vector<string> input = read_input("template.txt");

    for (auto l : input) {

        auto tokens = split(l,"|*%^");
        cout << l << " -> ";
        for (auto t : tokens)
            cout << t << " ";
        cout << "\n";
    }
}