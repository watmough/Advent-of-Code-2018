// Advent of Code 2018
// Day 14 - Chocolate Charts

#include "aoc.hpp"
using namespace std;

//#define PUZZLE_INPUT "37"           // test input
#define PUZZLE_INPUT "320851"     // puzzle input

int main()
{
    auto elves{map<int,int>()};
    auto recipes{vector<int>()};
    for (auto ch : string(PUZZLE_INPUT)) 
        recipes.push_back(ch-'0');
    // set elf start points
    for (auto elf{0};elf<2;++elf)
        elves[elf] = elf;
    while (1) {
        // combine recipes  by summing digits
        auto sum=accumulate(begin(elves),end(elves),0,[&](const auto& t,const auto& e){return t+recipes[e.second];});
        // add recipe digits
        auto sumd=to_string(sum);
        cout << "New recipe is " << sumd << "\n";
        for_each(begin(sumd),end(sumd),[&](const auto& d){recipes.push_back(d-'0');});
        for_each(begin(sumd),end(sumd),[&](const auto& d){part1.push_back(d-'0');});
        // step elves forward 1+current recipe, wrapping to new length of recipe list
        for (auto elf{0};elf<2;++elf) {
            elves[elf] = (elves[elf]+1+recipes[elves[elf]]) % recipes.size();
            cout << "elf " << elf << " -> pos " << elves[elf] << "\n";
        }
        // Look for 10 digits
        if (recipes.size()>=stoi(PUZZLE_INPUT)+10) {
            cout << "Part 1: Added 10 digits: "; 
            for_each( begin(recipes)+stoi(PUZZLE_INPUT),end(recipes),[](const auto& d){cout << d << " ";});
            cout << "\n";
            break;
        }
    }
}

/*
That's not the right answer; your answer is too low. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again. (You guessed 5104102441.) [Return to Day 14]

That's not the right answer; your answer is too low. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again. (You guessed 4821616122.) [Return to Day 14]

That's not the right answer; your answer is too low. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again. (You guessed 5104102441.) [Return to Day 14]
*/
