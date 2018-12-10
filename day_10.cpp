// Advent of Code 2018
// Day 10 - The Stars Align

#include "aoc.hpp"
using namespace std;

struct is_delim : std::unary_function<const char&, bool> {
    bool operator()(const char& c) const { return strchr("<,>",int(c))!=nullptr; }
};

void print_message(vector<tuple<long,long,long,long>> pointdata,int t,
                   long minx,long miny,long maxx,long maxy) {
    auto xw{maxx-minx+1},yw{maxy-miny+1};
    auto display{string(xw*yw,'.')};
    for (auto pv : pointdata) {
        auto x{get<0>(pv)},y{get<1>(pv)},vx{get<2>(pv)},vy{get<3>(pv)};
        x+=vx*t; y+=vy*t;
        display[(y-miny)*xw+x-minx]='X';
    }
    for (auto y{0};y<yw;++y)
        cout << display.substr(y*xw,xw) << "\n";
}

int main(int argc, char* argv[])
{
    auto input = read_input("day_10.txt");
    vector<tuple<long,long,long,long>> pointdata;
    for (auto l : input) {
        auto tokens = split(begin(l),end(l),is_delim());
        pointdata.push_back(make_tuple(stoi(tokens[1]),stoi(tokens[2]),
                                       stoi(tokens[4]),stoi(tokens[5])));
    }
    // step through time until stars align
    auto t{0};
    auto minarea{-1ll};
    while (true) {
        // get min/max x,y at time t
        long long minx{0ll},miny{0ll},maxx{0ll},maxy{0ll};
        for (auto pv : pointdata) {
            auto x{get<0>(pv)},y{get<1>(pv)},vx{get<2>(pv)},vy{get<3>(pv)};
            x+=vx*t; y+=vy*t;
            minx=x<minx?x:minx; miny=y<miny?y:miny;
            maxx=x>maxx?x:maxx; maxy=y>maxy?y:maxy;
        }
        // calc area
        auto area = (maxx-minx+1)*(maxy-miny+1);
        // check if area is bigger than seen so far
        if (minarea!=-1 && area>=minarea) {
            cout << "Smallest area " << minarea << " seen at t = " << t-1 << "\n";
            print_message(pointdata,t-1,minx,miny,maxx,maxy);
            break;
        }
        // otherwise
        minarea = area;
        t++;
    }
}
