// Advent of Code 2018
// Day 09 - Marble Mania

#include "aoc.hpp"
using namespace std;

void print(int c,deque<int> b,int p) {
    cout << "[" << p+1 << "] ";
    for (auto i=0;i<b.size();++i)
        if (c==i)   cout << "(" << b[i] << ")";
        else        cout << " " << b[i] << " ";
    cout << "\n";
}

void whatarethescoresgeorgedawes(map<int,int> s) {
    int m{},p{};
    for (auto s : s) {
        cout << "Player: " << s.first << " scored " << s.second << "\n";
        if (s.second>m) { m=s.second, p=s.first; };
    }
    cout << "Winner: " << p << " with " << m << "\n";
}

int nplayer(int p, int players) {
    return (p+1)%players;
};

int npos(int c,int s,int m)
{
    // first two positions
    if (s==0) return 0;
    if (s==1) return 1;

    // move two to the right
    c+=2;
    if (c>s)
        c=c-s;
    return c;
}

int bpos(int c,int s)
{
    // move 7 spots left
    c-=7;
    if (c<0)
        c+=s;
    return c;
}

// 405 players; last marble is worth 71700 points
int main()
{
    // auto players{9};
    // auto marbles{25};
    // auto players{10};
    // auto marbles{1618};
    // Part 1
    // auto players{405};
    // auto marbles{71700};
    // Part 1
    auto players{405};
    auto marbles{71700};

    auto b{deque<int>{}};
    auto s{map<int,int>{}};
    auto c{0},p{0},m{0};       // size, current, player [0 indexed], marble

    b.insert(begin(b),0);
    for (m=1;m<=marbles;++m,p=nplayer(p,players)) {

        if (m%23!=0) {
            // normal move - position
            c = npos(c,b.size(),m);
            // insert into board
            b.insert(begin(b)+c,m);        
        } else {
            // score marble value
            s[p]+=m;
            // move back 7 spots, score marble and remove marble
            c = bpos(c,b.size());
            s[p]+=*(begin(b)+c);
            b.erase(begin(b)+c);
        }
        
        // print game pos
//        print(c,b,p);
    }
    whatarethescoresgeorgedawes(s);
}




