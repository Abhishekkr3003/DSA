#include <limits.h>
#include <ctype.h>
#include "rajasthanGeography.h"

char *squeeze(char *begin, char *end)
{
    /* Squeeze out superflous white spaces */

    char *last, *start = begin;
    int first = 0;
    /* Set start to the first non space */
    while (isspace(*start))
        start++;
    /* locate last non space */
    while (isspace(*end) || *end == '\0')
        *(end--) = '\0';
    last = end;
    while (last >= start)
    {
        while (first && isspace(*last))
            last--;
        first = isspace(*last);
        *(end--) = *(last--);
    }
    return end + 1;
}
void setUpGraph(void)
{
    int i, distance;
    
    FILE *cities = fopen("cities", "r");
    FILE *roads = fopen("roads", "r");
    assert(cities != NULL && roads != NULL);
    
    char name[100];
    char *roadStart, *roadEnd, *kms;
    struct link *ll;
    
    while (fgets(name, 99, cities))
    {
        if (strlen(name) < 2)
            break;
        name[strlen(name) - 1] = '\0';
        if (makeTown(squeeze(name, name + strlen(name))) == NULL)
            break; // Data structure full
    }
    while (fgets(name, 99, roads))
    {
        if (strlen(name) < 4)
            break;
        name[strlen(name) - 1] = '\0';
        roadStart = kms = name;
        while (!isdigit(*kms))
            kms++;
        *(kms - 1) = '\0';
        sscanf(kms, "%d", &distance);
        roadEnd = kms;
        while (!isspace(*roadEnd))
            roadEnd++;
        linkTowns(squeeze(roadStart, roadStart + strlen(roadStart)),
                  squeeze(roadEnd, roadEnd + strlen(roadEnd)), distance);
    }
}

void findShortestDistances(struct town *here)
{
    /* Distances to other towns from HERE */
    int townsIdx, update = 0;
    if (here == NULL)
        return;

    here->flag1=1;
    printf("%s - Rupa Ki Nangal - %d kms\n",here->name, getDistFromStart(here));
    int nextDist;
    struct town *newFound=NULL, *there=NULL;
    struct link *link=NULL;
    
    link=getLink2newestNeighbour(here);
    while (link != NULL)
    {
        newFound = getOtherTown(here, link);
        assert(newFound != NULL);
        //printf("%s\n", next_city->name);
        if (newFound->flag1 == 0)
        {
            if(getDistFromStart(here)+length(link)<getDistFromStart(newFound))
                setDistFromStart(newFound, getDistFromStart(here)+length(link));
        }
        link = getLink2earlierNeighbour(here, link);
    }

    there=NULL;
    int mini=INT_MAX;
    for (townsIdx = 0; townsIdx < towns; townsIdx++)
    {
        if(townships[townsIdx]->flag1==0 && (getDistFromStart(townships[townsIdx])<mini))
        {
            mini=getDistFromStart(townships[townsIdx]);
            there=townships[townsIdx];
        }
    }  
    //< 20 Lines of C code removed. Student to add code here for Task 03 >
    /* recursive call from town closest to the starting town
Whose distance is not yet final */
    findShortestDistances(there);
}

void sort()
{
    struct town *copy[TOWNS];
    for (int i=0; i<towns;i++)
        copy[i]= townships[i];
    int i,j;
    struct town*temp;
    for (i=0;i<towns;i++)
    {
        for (j=0;j<towns-1-i; j++)
        {
            if (copy[j]->finalisedDist > copy[j+1]->finalisedDist)
            {
                temp=copy[j];
                copy[j]=copy[j+1];
                copy[j+1]=temp;
            }
        }
    }
    printf("\nDistance of neigbouring towns of Rupa Ki Nangal:-\n");
    for(i=0;i<towns;i++)
        printf("Town %s (%d kms away from Rupa Ki Nangal)\n", getName(copy[i]), (copy[i])->finalisedDist);

}

void BFS(struct town *rupaNangal)
{
    printf("Initiating BFS............\n");
    struct town *city, *next_city;
    struct link* link;
    rupaNangal->flag2=1;
    
    insert_in_queue(rupaNangal);
    rupaNangal->finalisedDist=0;
    while(!isEmpty())
    {
        city=remove_from_queue();
        assert(city!=NULL);
        printf("Town Visited: %s\n", getName(city));
        link=getLink2newestNeighbour(city);
        
        while(link!=NULL)
        {
            next_city=getOtherTown(city, link);
            //printf("-->%s\n", neighbour(city, link));
            assert(next_city!=NULL);
            //printf("%s\n", next_city->name);
            if(next_city!=NULL && next_city->flag2==0)
            {
                insert_in_queue(next_city);
                next_city->finalisedDist=city->finalisedDist+length(link);
                next_city->flag2=1;
            }          
            link=getLink2earlierNeighbour(city, link);
        }
    }
    printf("********************************************************************************\n");
    sort();
    printf("********************************************************************************\n");
}


int main(void)
{
    int townsIdx;
    struct town *rupaNangal;
    setUpGraph();
    rupaNangal = getTown("Rupa ki Nangal");
    assert(rupaNangal != NULL);
    BFS(rupaNangal);
    setFinalDist(rupaNangal, 0);

    printf("\nShortest Distances from Rupa Ki Nangal in increasing order:-\n");
    findShortestDistances(rupaNangal);

    /* Print distances. */
    printf("********************************************************************************\n");
    printf("\nShortest Distance from LNMIIT:-\n");
    for (townsIdx = 0; townsIdx < towns; townsIdx++)
    {
        printf("Town %s is ", getName(townships[townsIdx]));
        if (isDistanceFinal(townships[townsIdx]))
            printf("%d kms from LNMIIT\n",
                   getDistFromStart(townships[townsIdx]));
        else
            printf("unconnected to LNMIIT in this graph\n");
    }
    printf("********************************************************************************\n");
    return 0;
}