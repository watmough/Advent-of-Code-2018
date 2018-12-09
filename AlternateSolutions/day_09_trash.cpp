// Advent of Code 2018
// Day 09 - Marble Mania

#include "aoc.hpp"
using namespace std;

int next_pos(int current, int marble)
{
    if (marble==0)         return 0;
    if (marble%23==0)       return (current-7)%marble;
    if (current+2>marble)   return 1-((marble/23)%2);
    return current+2;
}

// 405 players; last marble is worth 71700 points

int main(int argc, char* argv[])
{
    auto players = 9;
    auto marbles = 25;

    auto player=0;
    auto current=0;
    auto marble=0;

    auto b{vector<int>{}};
    while (marble!=marbles) {
        if (b.size()==0) {
            b.push_back(marble++);
            continue;
        }
        rotate
    }

    // while (marble!=marbles) {
    //     current=next_pos(current,marble);
    //     cout << "Play " << marble << " of " <<marble+1 << " at " << current << "\n";
    //     marble++;
    // }

     auto score{map<int,int>{}};
//     auto circle = vector<int>{};
//     circle.push_back(marble++);
// //    circle.push_back(999);
//     while (marble!=marbles) {
//         cout << "m:" << marble << "\n";
//         if (marble%23==0) {
//             score[player]+=marble++;
//             auto remove = begin(circle)+(circle.size()+current)%circle.size();
//             score[player]+=*remove;
//             circle.erase(remove);
//             current=(current-1)%circle.size();
//         } else {
//             auto play{next_pos(current,marble)};
//             cout << "play: " <<play << "\n";
//             auto pos = begin(circle)+play;
//             circle.insert(pos,marble++);
//             current=distance(begin(circle),pos);
//         }
//         for (auto p : circle)
//             cout << p << " ";
//         cout << "\n";
//         player = (player+1)%players;
//     }
    for (auto s : score)
        cout << "score: " << s.second << "\n";
}