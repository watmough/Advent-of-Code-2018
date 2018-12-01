// Advent of Code 2018
//
// Day 01 - 

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
    ifstream ifs("template.txt",ifstream::in);
    vector<string> input = read_input(ifs);

    for (auto l : input) {
        cout << l << "\n";
    }
}