// Advent of Code 2018
// Day 07 - 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int fun(char * s) {
    return s-s;
}

int main()
{
#if 0
    #include "template.h"
#else
    char orig[] = "testdata";
    char data[] = "testdata";
#endif
    int l = fun(data);
    printf("Part 1: ...: \n");

    int m = abs(l);
    printf("Part 2: ...: \n");
    return 0;
}
