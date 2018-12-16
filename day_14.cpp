// Advent of Code 2018
// Day 14 - Chocolate Charts

#include "aoc.hpp"
using namespace std;

#define PUZZLE_INPUT "320851"

int main()
{
    auto elves{map<int,int>()};
    auto recipes{vector<int>{3,7}};     // dammit! you stick with the example initial recipes
    auto digits{vector<int>{3,2,0,8,5,1}};
//    auto digits{vector<int>{5,9,4,1,4}};    // test input yielding 2018
    // set elf start points
    for (auto elf{0};elf<2;++elf)
        elves[elf] = elf;
    auto part1{true};
    while (1) {
        // combine recipes  by summing digits
        auto sum=accumulate(begin(elves),end(elves),0,[&](const auto& t,const auto& e){return t+recipes[e.second];});
        // add recipe digits
        auto sumd=to_string(sum);
        for_each(begin(sumd),end(sumd),[&](const auto& d){recipes.push_back(d-'0');});
        // step elves forward 1+current recipe, wrapping to new length of recipe list
        for (auto elf{0};elf<2;++elf) {
            elves[elf] = (elves[elf]+1+recipes[elves[elf]]) % recipes.size();
        }
        // Look for 10 digits
        if (part1&&recipes.size()>=stoi(PUZZLE_INPUT)+10) {
            cout << "Part 1: Added 10 digits: "; 
            for_each( begin(recipes)+stoi(PUZZLE_INPUT),end(recipes),[](const auto& d){cout << d << " ";});
            cout << "\n";
            part1=false;
        }
        // look for puzzle input in output string
        if (recipes.size()>digits.size()) {
            auto it=end(recipes)-digits.size()-1;
            if (equal(begin(digits),end(digits),it)||equal(begin(digits),end(digits),++it)) {
                cout << "Part 2: To the left there are " << distance(begin(recipes),it) << "\n";
                break;
            }
        }
    }
}

/*
That's not the right answer; your answer is too low. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again. (You guessed 5104102441.) [Return to Day 14]

That's not the right answer; your answer is too low. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again. (You guessed 4821616122.) [Return to Day 14]

That's not the right answer; your answer is too low. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute before trying again. (You guessed 5104102441.) [Return to Day 14]
*/
