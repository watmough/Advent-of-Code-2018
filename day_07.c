// Advent of Code 2018
// Day 07 - 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#if 0
    #define FILENAME "day_07.txt"
    #define COUNT 101
#else
    #define FILENAME "day_07_tst.txt"
    #define COUNT 7
#endif

char pre[COUNT];
char ste[COUNT];
char all[COUNT*2] = "";

int needswap(char l, char r);
int canswap(char l, char r);

int main()
{

    // Step T must be finished before step W can begin.
        // read data
    FILE *f = fopen(FILENAME,"rb");
    char fs,ss;
    int c=0;
    while (!feof(f) && fscanf(f,"Step %c must be finished before step %c can begin.\n",&fs,&ss)) {
        printf("%c -> %c\n",fs,ss);
        pre[c]=fs;
        ste[c++]=ss;

        // add letters
        if (strchr(all,fs)==NULL) strncat(all,&fs,1);
        if (strchr(all,ss)==NULL) strncat(all,&ss,1);

        printf("String %s\n",all);
    }
    fclose(f);

    // for each step, find 


    // sort alpha first
    for (int i=0;i<strlen(all)-1;++i) {
        for (int j=i+1;j<strlen(all);++j) {
            // sort steps in order of preq / alpha
            char l=all[i];
            char r=all[j];
            if ((needswap(l,r))||(r<l&&canswap(l,r))) {//||needswap(l,r)) {
                all[i]=r;
                all[j]=l;
                printf("%c before %c -> %s\n",r,l,all);
            }
        }
    }
    printf("String sorted %s\n",all);


    // for (int i=0;i<strlen(all)-1;++i) {
    //     for (int j=i+1;j<strlen(all);++j) {
    //         // sort steps in order of preq / alpha
    //         char l=all[i];
    //         char r=all[j];
    //         if (needswap(l,r)) {
    //             all[i]=r;
    //             all[j]=l;
    //             printf("%c before %c -> %s\n",r,l,all);
    //         }
    //     }
    // }
    // printf("Order: %s\n",all);

    printf("Part 1: ...: \n");

    printf("Part 2: ...: \n");
    return 0;
}

int needswap(char l, char r)
{
    printf("Comparing %c and %c\n",l,r);
    for (int i=0;i<COUNT;++i) {
        if (pre[i]==r && ste[i]==l) 
            return 1;
    }
    return 0;
}

int canswap(char l, char r)
{
    printf("Can swap %c and %c: ",l,r);
    for (int i=0;i<COUNT;++i) {
        if (pre[i]==l && ste[i]==r) {
            printf("no\n");
            return 0;
        }
    }
    printf("yes\n");
    return 1;
}



// answer 1: YPDXTHOLNCSQMGEAZKIRBUWVFJ
// That's not the right answer. If you're stuck, there are some general tips on the about page, or you can ask for hints on the subreddit. Please wait one minute 
//before trying again. (You guessed YPDXTHOLNCSQMGEAZKIRBUWVFJ.) [Return to Day 7]
