#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>

#define TOWNS 100
extern struct town *townships[];
extern int towns;

struct town
{
    char *name;
    struct link *edges;
    int townIdx, finalisedDist, flag1, flag2; // As needed
    int distance;                              // Distance from the origin town
};

struct link
{
    /* The link connects these towns */
    int lowIdx, highIdx; // Indices in array townships
    int length;
    // Distance between towns
    struct link *nxtLowEdge, *nxtHighEdge;
};

/* Functions to make towns and link them */
struct town *makeTown(char *name);
void linkTowns(char *thisTown, char *thatTown, int distance);
/* Get town from NAME */
struct town *getTown(char *name);
/* Get name for TOWN */
char *getName(struct town *town);
/* ADT interface fucntions for link related needs */
/* To support iteration and looping */
/* get link that connects HERE to the last neighbour
connected to it */
struct link *getLink2newestNeighbour(struct town *here);
/* Get link that connects HERE to the neighbour before
the one connected by LINK. */
struct link *getLink2earlierNeighbour(struct town *here, struct link *link);
/* Other utility functions */
/* Get pointer to other town on ROAD */
struct town *getOtherTown(struct town *here, struct link *road);
/* Get length of ROAD */
int length(struct link *road);
/* Get name of town connected to HERE by ROAD */
char *neighbour(struct town *here, struct link *road);
/* Return distance from the origin node */
int getDistFromStart(struct town *destination);
/* Set distance to town from origin return new distance*/
int setDistFromStart(struct town *destination, int distance);
/* Set final distance to town from origin returns distance
Further reassignement to distances are ignored */
int setFinalDist(struct town *destination, int distance);
/* Returns 1 if HERE has final distance set */
int isDistanceFinal(struct town *here);

/* Making of Queue for the breadth first search*/
struct town *queue[TOWNS];
void insert_in_queue(struct town *town);
struct town *remove_from_queue();
int isEmpty();
