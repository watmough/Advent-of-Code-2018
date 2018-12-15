// Advent of Code 2018
// Day 11 - Chronal Charge

#include "aoc.hpp"
using namespace std;

// evaluate 3x3 cells with top-left at x,y
int64_t at3x3(int64_t x, int64_t y, int64_t s, int64_t serial_number)
{
    int64_t total{0};
    for (int px = 0; px < s; ++px)
    {
        for (int py = 0; py < s; ++py)
        {
            int64_t rack_id{x + px + 10};
            int64_t step2 = rack_id * (y + py);
            int64_t step3 = step2 + serial_number;
            int64_t step4 = step3 * rack_id;
            int64_t step5 = ((step4 / 100) % 10) - 5;
            total += step5;
        }
    }
    return total;
}

#define PUZZLE_INPUT 5535

int main(int argc, char *argv[])
{
    //    assert(at3x3(3,5,8)==4);

    // Part 1 - find best 3x3 square of fuel cells
    int64_t x{0}, y{0}, sp{0}, max_power{0};
    for (int s = 1; s < 300; ++s)
    {
        {
            for (int r = 1; r < 300 - s + 1; ++r)
            {
                for (int c = 1; c < 300 - s + 1; ++c)
                {
                    int64_t value = at3x3(c, r, s, PUZZLE_INPUT);
                    if (value > max_power)
                    {
                        max_power = value;
                        x = c;
                        y = r;
                        sp = s;
                    }
                }
            }
        }
        cout << "Max power of " << max_power << " at " << x << " " << y << " " << sp << "\n";
    }
}
