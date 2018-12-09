// Advent of Code 2018
// Day 09 - Marble Mania

#include "aoc.hpp"
using namespace std;

template <typename Iter>
void print_board(int player, const Iter& first, const Iter& last, const Iter& pos) {
    cout << "[" << player << "] ";
    for (auto it=first;it!=last;++it)
        if (it==pos) cout << "(" << *it << ")";
        else         cout << " " << *it << " ";
    cout << "\n";
}

template <typename Tscore>
pair<int,Tscore> whatarethescoresgeorgedawes(map<int,Tscore> scores) {
    auto chickendinner{Tscore{}};
    auto winner{0};
    for (auto s : scores) {
        if (s.second>chickendinner) { chickendinner=s.second, winner=s.first; };
    }
    cout << "Winner: " << winner << " with " << chickendinner << "\n";
    return make_pair(winner,chickendinner);
}

template <typename Tscore>
pair<int,Tscore> play_game(int players, int marbles, std::string part="") {
    auto b{list<int>{0}};
    auto score{map<int,Tscore>{}};
    auto player{0};
    auto pos{b.begin()};
    for (auto marble=1;marble<=marbles;++marble, player=(player+1)%players) {
        if (marble%23!=0) {
            for (auto i{0};i<2;++i) { if (pos==end(b)) pos=begin(b); pos++; }
            pos=b.insert(pos,marble);
        } else {
            for (auto i{0};i<7;++i) { if (pos==begin(b)) pos=end(b); pos--; }
            score[player]+=marble+*pos;
            pos=b.erase(pos);
        }
        if (marbles<100)
            print_board(player+1,begin(b),end(b),pos);
    }
    cout << part;
    return whatarethescoresgeorgedawes(score);
}

// Puzzle input: 405 players; last marble is worth 71700 points
int main(int argc, char **argv)
{
    play_game<int>(9,25);
    play_game<int>(10,1618);
    play_game<int>(13,7999);
    play_game<int>(17,1104);
    play_game<int>(21,6111);
    play_game<int>(30,5807);
    play_game<uint64_t>(405,71700,string("Part 1: "));
    play_game<uint64_t>(405,71700*100,"Part 2: ");
}
