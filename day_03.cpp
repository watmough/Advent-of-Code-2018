// Advent of Code 2018
// Day 03 - No Matter How You Slice It

#include "aoc.hpp"
using namespace std;

// bad: use a tuple instead for simple stuff
typedef struct claim {
    claim(int cl, int x1,int y1, int x2, int y2) : 
        cl(cl), x1(x1), y1(y1), x2(x2), y2(y2) {};

    int cl;
    int x1,y1,x2,y2;
} claim;

int main(int argc, char* argv[])
{
    vector<string> input = read_input("day_03.txt");

    // Part 1: Find the total area that overlaps between the claims
    auto cl=0;
    char c;
    auto ct=0;
    vector<claim> claims;
    map<int,map<int,int>> dots;
    for (auto l : input) {
        // need a better parser strategy, helpers
        stringstream ss(l);
        auto x1=0,y1=0,x2=0,y2=0;
        ss >> c >> cl;
        while (c!='@') ss >> c;
        ss >> x1;
        while (c!=',') ss >> c;
        ss >> y1;
        while (c!=':') ss >> c;
        ss >> x2; x2+=x1-1;
        while (c!='x') ss >> c;
        ss >> y2; y2+=y1-1;
        cout << cl << " " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
        // create a claim
        auto a = claim(cl,x1,y1,x2,y2);
        claims.push_back(a);

        // iterate over area in this claim and put it in the dict
        for (int i=x1;i<=x2;++i) {
            for (int j=y1;j<=y2;++j) {
                dots[i][j]++;
                if (dots[i][j]==2)
                    ct++;
            }
        }
    }
    cout << "Part 1: Overlapping area: " << ct << "\n";

    // Part 2 - Find the one claim that does not overlap any others
    for (auto c : claims) {
        // find a 
        auto overlap = false;
        for (int i=c.x1;i<=c.x2;++i) {
            for (int j=c.y1;j<=c.y2;++j) {
                if (dots[i][j]!=1)
                    overlap=true;
            }
        }
        if (!overlap) {
            cout << "Part 2: Claim " << c.cl << "\n";
        }
    }

    // 'working' but incorrect code to (double)count conflicting claims

    // auto ct=0l;
    // for_all_pairs(begin(claims),end(claims),[&](const auto& c1,const auto& c2) {
    //     if ((c1.x1<=c2.x2&&c1.x2>=c2.x1&&c1.y1<=c2.y2&&c1.y2>=c2.y1)) {
    //         cout << "claim " << c1.cl << " and " << c2.cl << " intersect\n";
    //         cout << "c1: " << c1.cl << " " << c1.x1 << " " << c1.y1 << " " << c1.x2 << " " << c1.y2 << "\n";
    //         cout << "c2: " << c2.cl << " " << c2.x1 << " " << c2.y1 << " " << c2.x2 << " " << c2.y2 << "\n";
    //         cout << "x len: " << (min(c1.x2,c2.x2)-max(c1.x1,c2.x1))+1 << "\n";
    //         cout << "y len: " << (min(c1.y2,c2.y2)-max(c1.y1,c2.y1))+1 << "\n";
    //         cout << "area: " << ((min(c1.x2,c2.x2)-max(c1.x1,c2.x1))+1)*((min(c1.y2,c2.y2)-max(c1.y1,c2.y1))+1) << "\n";
    //         ct+=(min(c1.x2,c2.x2)-max(c1.x1,c2.x1)+1)*(min(c1.y2,c2.y2)-max(c1.y1,c2.y1)+1);
    //     }
    // });
    // cout << "Area: " << ct << "\n";
}

