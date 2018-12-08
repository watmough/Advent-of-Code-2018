// Advent of Code 2018
// Day 0x - 

#include "aoc.hpp"
using namespace std;

int sum_meta()
{
    int c{},m{},total{};
    cin >> c >> m;
    while (c--) 
        total+=sum_meta();
    while (m--) {
        int v{}; cin >> v;
        total+=v;
    }
    return total;
}

int sum_nodes()
{
    int c{},m{},total{};
    vector<int> children;
    cin >> c >> m;
    while (c--)
        children.push_back(sum_nodes());
    while (m--) {
        int v{}; cin >> v;
        if (children.empty())
            total+=v;
        else if (v>0&&v-1<children.size())
            total+=children[v-1];
    }
    return total;
}

int main(int argc, char* argv[])
{
    if (argc<2) {
        cout << "Usage: " << argv[0] << " 1|2 < data.txt\n";
        exit(0);
    }
    if (atoi(argv[1])==1)
        cout << "Part 1: Metadata sum: " << sum_meta() << "\n";
    else
        cout << "Part 2: Nodes sum: " << sum_nodes() << "\n";
}