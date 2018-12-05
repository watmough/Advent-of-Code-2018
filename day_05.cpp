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
