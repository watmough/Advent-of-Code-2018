// Advent of Code 2018
// Day 13 - Mine Cart Madness

#include "aoc.hpp"
using namespace std;

int main() 
{
    enum dir {n,e,s,w};
    enum turn {l,t,r};
    int stepx[] = {0,1,0,-1};   // indexed by dir enum
    int stepy[] = {-1,0,1,0};   // indexed by dir enum
    dir corner_tl_br[] = {e,n,w,s}; // next direction for /
    dir corner_tr_bl[] = {w,s,e,n}; // next direction for \ ...
    dir turndir[3][4] = {{w,n,e,s},{n,e,s,w},{e,s,w,n}};
    turn nextturn[] = {t,r,l};  // 
    using cart = tuple<int,int,dir,turn,bool>;

    auto input{read_input("day_13.txt")};
    vector<cart> carts;
    for (auto y{0};y<input.size();++y) {
        for (auto x{0};x<input[y].size();++x) {
            char ch = input[y][x];
            if (ch=='<'||ch=='>'||ch=='v'||ch=='^') {
                dir d = ch=='<'?w:ch=='>'?e:ch=='^'?n:s;
                carts.push_back(make_tuple(x,y,d,l,true));
            }
        }
    }

    auto clock{0},crashes{0};
    while (1) {
        for (auto it=begin(carts);it!=end(carts);++it) {
            auto& cart=*it;
            if(!get<4>(cart)) continue;
            auto& x{get<0>(cart)};  // x ref
            auto& y{get<1>(cart)};  // y ref
            auto& d{get<2>(cart)};  // direction ref
            auto& t{get<3>(cart)};  // next turn ref
            // process move and directions
            auto nx=x+stepx[d];
            auto ny=y+stepy[d];
            char ch=input[ny][nx];
            switch (ch) {
            case '/':
                d=corner_tl_br[d];
                break;
            case '\\':
                d=corner_tr_bl[d];
                break;
            case '+':
                d=turndir[t][d];
                t=nextturn[t];
                break;
            }
            // check for collision
            auto cit=find_if(begin(carts),end(carts),[&](auto& c){return (get<0>(c)==nx&&get<1>(c)==ny&&get<4>(c)==true);});
            if (cit!=end(carts)) {
                cout << "cart at " << x << "," << y << " crashes into " << nx << "," << ny << "\n";
                if (crashes++==0)
                    cout << "Part 1: First collision at: " << nx << "," << ny << "\n";
                x=nx,y=ny;              // do the actual move, then mark crashed carts
                for_each(begin(carts),end(carts),[&](auto& c){if((get<0>(c)==nx&&get<1>(c)==ny)&&get<4>(c)) {cout << "Killed a cart\n";get<4>(c)=false;}});
            } else {
                x=nx,y=ny;              // do the actual move, then erase this location
            }
        }
        carts.erase(remove_if(begin(carts),end(carts),[&](auto& c){return get<4>(c)==false;}),end(carts));
        sort(begin(carts),end(carts),[&](const cart& l,const cart& r){  // sort by y,x
            return get<0>(l)<get<0>(r)||(get<0>(l)==get<0>(r)&&get<1>(l)<get<1>(r));
        });
        if (carts.size()==1) {
            cout << "Part 2: Last cart is at " << get<0>(carts.front()) << "," << get<1>(carts.front()) << "\n";
            break;
        }
        ++clock;
    }
}

