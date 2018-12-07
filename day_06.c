// Advent of Code 2018
// Day 06 - 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIDE 400            // custom for my problem data
#define POINTS 50+1
#define FILENAME "day_06.txt"
#define PART2 10000

// #define SIDE 10             // test data
// #define POINTS 6+1
// #define FILENAME "day_06_tst.txt"
// #define PART2 32

int coords[(POINTS+1)*2];   // Points x,y
int unbounded[POINTS+1];    // set if infinite

int owner[SIDE*SIDE];       // Grid owned by point
int dist[SIDE*SIDE];      
int visited[SIDE*SIDE];

int minx=SIDE,miny=SIDE,maxx=0,maxy=0;
int inbounds(int x, int y) {
    if (x<minx||x>maxx||y<miny||y>maxy)
        return 0;
    return 1;
}

int ffarea(int x, int y, int area)
{
    if (visited[y*SIDE+x]) 
        return 0;

    visited[y*SIDE+x]=1;

    if (inbounds(x,y-1)) area+=ffarea(x,y-1,1);
    if (inbounds(x,y+1)) area+=ffarea(x,y+1,1);
    if (inbounds(x+1,y)) area+=ffarea(x+1,y,1);
    if (inbounds(x-1,y)) area+=ffarea(x-1,y,1);
    
    return area;
}

int ffdist(int x, int y, int p, int area)
{
    if (visited[y*SIDE+x]) 
        return 0;
    visited[y*SIDE+x]=1;

    int d = abs(x-coords[2*p])+abs(y-coords[2*p+1]);
    if (d==0 || (dist[y*SIDE+x]==0 && owner[y*SIDE+x]==0) || d<dist[y*SIDE+x]) {                 // take ownership
        dist[y*SIDE+x]=d;
        owner[y*SIDE+x]=p;
    } else if (d==dist[y*SIDE+x] && owner[y*SIDE+x]!=p) {         // tie
        owner[y*SIDE+x]=0;
        area=0;
        return area;
    } else if (d>dist[y*SIDE+x]) {          // not ours
        area=0;
        return area;
    }

    if (inbounds(x,y-1)) area+=ffdist(x,y-1,p,1); else unbounded[p]=1;
    if (inbounds(x,y+1)) area+=ffdist(x,y+1,p,1); else unbounded[p]=1;
    if (inbounds(x+1,y)) area+=ffdist(x+1,y,p,1); else unbounded[p]=1;
    if (inbounds(x-1,y)) area+=ffdist(x-1,y,p,1); else unbounded[p]=1;
    
    return area;
}

void ffdistsum(int x, int y, int p)
{
    if (visited[y*SIDE+x]) 
        return;
    visited[y*SIDE+x]=1;

    int d = abs(x-coords[2*p])+abs(y-coords[2*p+1]);
    dist[y*SIDE+x]+=d;

    if (inbounds(x,y-1)) ffdistsum(x,y-1,p);
    if (inbounds(x,y+1)) ffdistsum(x,y+1,p);
    if (inbounds(x+1,y)) ffdistsum(x+1,y,p);
    if (inbounds(x-1,y)) ffdistsum(x-1,y,p);
}

int main()
{
    // read data
    FILE *f = fopen(FILENAME,"rb");
    int x,y,p=1;
    while (!feof(f) && fscanf(f,"%d,%d",&x,&y)) {
        // save points
        coords[p*2]=x;
        coords[p*2+1]=y;

        // track x,y min max
        minx=x<minx?x:minx;
        miny=y<miny?y:miny;
        maxx=x>maxx?x:maxx;
        maxy=y>maxy?y:maxy;

        // done a point
        p++;
    }
    fclose(f);

    // Part 1 - Find the largest bounded region
    // for each point
    int maxarea=0;
    for (int pass=0;pass<2;++pass) {
        memset(unbounded,'\0',sizeof(unbounded));
        for (p=1;p<POINTS;++p) {
            // flood fill to establish boundaries
            memset(visited,'\0',sizeof(visited));
            // for (int c=0;c<100;++c)
            //     printf(" %c %s",(owner[c]==0?'.':'a'+owner[c]-1),(c+1)%10==0?"\n":"");
            int area = ffdist(coords[p*2],coords[p*2+1],p,1);
            if (pass==1&&unbounded[p]==0&&area>maxarea)
                maxarea = area;
            // printf("Point %d Area: %d Unbounded: %d\n",p,area,unbounded[p]);
        }
    }
    printf("Part: Max area: %d\n",maxarea);

    // Part 2 - Find the area of the region with a sum of distances of <10000
    memset(dist,'\0',sizeof(dist));
    for (p=1;p<POINTS;++p) {
        // flood fill and sum
        memset(visited,'\0',sizeof(visited));
        // for (int c=0;c<100;++c)
        //     printf(" %c %s",(owner[c]==0?'.':'a'+owner[c]-1),(c+1)%10==0?"\n":"");
        ffdistsum(coords[p*2],coords[p*2+1],p);
    }

    int region=0;
    for (int i=minx;i<maxx;++i) {
        for (int j=miny;j<maxy;++j) {
            if (dist[j*SIDE+i]<PART2) region++;
        }
    }
    printf("Part 2: Region is %d\n",region);

    return 0;
}
