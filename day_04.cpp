// Advent of Code 2018
// Day 04 - Repose Record

#include "aoc.hpp"
using namespace std;

struct is_delim : std::unary_function<const char&, bool> {
    bool operator()(const char& c) const { return strchr(" :[]#-",int(c))!=nullptr; }
};

const static bool compare(const pair<int,int>& a, const pair<int,int>& b)
{
    return (a.second<b.second);
}

int main(int argc, char* argv[])
{
    vector<string> input = read_input("day_04.txt");
    sort(begin(input),end(input));

    // build a map of guards to total sleep time and by minute asleep
    auto guard{0};
    auto wakeat{0};
    auto sleepat{59};
    auto sleeping = map<int,int>();
    auto minutes = map<int,array<int,60>>();
    for (auto l : input) {
        auto tokens = split(begin(l),end(l),is_delim());
        if (l.find("Guard")!=string::npos)  guard   = stoi(tokens[7]);
        if (l.find("asleep")!=string::npos) sleepat = stoi(tokens[5]);
        if (l.find("wake")) {
            wakeat = stoi(tokens[5]);
            cout << "Guard " << guard << " sleep " << sleepat << " wake " << wakeat << "\n";
            sleeping[guard]+=wakeat-sleepat;
            for (int i=sleepat;i<wakeat;++i) minutes[guard][i]++;
        }
    }

    // Part 1 - Find the sleepiest guard * the minute he spent most asleep
    auto g = max_element(begin(sleeping),end(sleeping),compare);
    cout << "Sleepiest guard: " << (*g).first << " slept " << (*g).second << " mins.\n";
    guard = (*g).first;
    auto m = max_element(begin(minutes[guard]),end(minutes[guard]));
    auto minute = m-minutes[guard].data();
    cout << "Part 1: Guard * Minutes: " << guard*minute << "\n";

    auto maxminutes = 0;
    auto mostminute = 0;
    auto mostguard = 0;
    for( auto g : minutes ) {
        guard = g.first;

        auto m = max_element(begin(minutes[guard]),end(minutes[guard]));
        auto minute = m-minutes[guard].data();
        cout << "g: " << guard << " Sleepiest minute " << minute << " for " << *m << "\n";

        if (*m>maxminutes) {
            maxminutes = *m;
            mostminute = minute;
            mostguard = guard;
        }
    }
    cout << "Part 2: Most frequently asleep guard * minute: " << mostguard << " m " << mostminute << " -> " << mostguard*mostminute << "\n";
}