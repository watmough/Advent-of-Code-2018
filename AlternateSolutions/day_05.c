// Advent of Code 2018
// Day 05 - Alchemical Reduction

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int react(char * s)
{
    char * r = s+1;
    char * w = s;
    // read over string reacting as we go
    while (*r) {
        // check for reaction
        if ((*r^*w)==('A'^'a')) 
            w--, r++;
        else
            *++w=*r++;
    }
    *++w='\0';

    // return length
    return w-s;
}

int main()
{
#if 1
    #include "day_05.h"
#else
    char o[] = "dabAcCaCBAcCcaDA";
    char s[] = "dabAcCaCBAcCcaDA";
#endif
    
    int l = react(s);
    printf("Part 1: Length: %d\n",l);

    int b = l;
    for (int i='a';i<='z';++i) {
        // copy from s to o, skipping i
        char *p=s,*q=o;
        while (*p)
            if (tolower(*p)==i)
                p++;
            else
                *q++=*p++;
        *q='\0';        

        // react o, track best length
        int c = react(o);
        b = c<b ? c : b;
    }
    printf("Part 2: Best length: %d\n",b);
    return 0;
}
