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
