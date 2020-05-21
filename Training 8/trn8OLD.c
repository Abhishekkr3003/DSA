/*
    Abhishek Kumar
    19ucs241
    Submitted on 12th May 2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>

#define TBLSZ 6000
int usedSize,          // Part of the table that will be used
    divider2ndHashing; // Step size for double hashing
double goldenNumber;
char *table[TBLSZ];
int initialise(int tableSize)
{
    /* Find two suitable prime values for two division hashings funtions. */
    /* usedSize should be a prime that is nearly as big as TBLSZ This sets the part of the table that is actually used to store pointers to strings */

    assert(TBLSZ > 1000);
    goldenNumber = (sqrt(5.0) + 1) / 2;
    int testing, prime, i;
    if (TBLSZ % 2 == 0)
        usedSize = TBLSZ - 1;
    else
        usedSize = TBLSZ;
    /* Begin with usedSize as big as TBLSZ and progressively lower it till it is a prime */

    while (usedSize > 2)
    { // Keep trying
        i = 3;
        while (i * i <= usedSize)
        {
            if (usedSize % i == 0)
            {
                /* No good */
                usedSize -= 2;
                break;
            }
            i += 2;
        }
        if (i * i > usedSize)
        {
            break;
        }
    }
    /* Pointers to data strings will be in indices 0 to usedSize. Now find a prime to do probing over the table */

    divider2ndHashing = 2;
    while (divider2ndHashing * divider2ndHashing < usedSize)
        divider2ndHashing *= 2;
    /* Similar to the previous search for a prime */
    while (divider2ndHashing > 2)
    { // Keep trying
        i = 3;
        while (i * i <= divider2ndHashing)
        {
            if (divider2ndHashing % i == 0)
            {
                /* No good */
                divider2ndHashing -= 2;
                break;
            }
            i += 2;
        }
        if (i * i > divider2ndHashing)
        {
            break;
        }
    }
}
int goldenMultiplicative(int key)
{
    /* Returns the primary location for the data using multiplication by golden number. See Reema Thareja Edn 2 page 468*/
    double multiplier = goldenNumber - 1;
    double frac = (key * multiplier);
    int index = frac;
    frac = frac - index;
    index = frac * TBLSZ;
    return index;
}
int makeNumber(char *str)
{
    /* Construct a number from teh string */
    assert(str != NULL);
    //printf("This is:%s\n", str);
    int num = 0;
    int el = strlen(str);
    int i = el - 1; // Next letter to process
    if (el % 2 == 0)
        el--;                  // Make it odd
    assert(el < 20 && el > 0); // Too long a word
    /* Computer specific limit on while */
    while (num < INT_MAX / 26 / 26)
    {
        //printf("%c ||num=%d, %d\n", str[i],num, toupper(str[i]) - toupper('A'));
        num = num * 26 + toupper(str[i]) - toupper('A');
        i = (i + 2) % el; // Choose alternate letters
    }
    num = 26 * num + el; // Include word length
    return num;
}
int divisionHash(int key, int probe)
{
    int step = key % divider2ndHashing;
    /* Linear hashing */
    return (key % usedSize + probe) % TBLSZ;
    /* Quadratic hashing */
    //return (key%usedSize + probe*probe)%TBLSZ;
    /* Double hashing */
    //return (key % usedSize + probe * step) % usedSize;
}

void search()
{
    FILE *keys = fopen("keys", "r");
    assert(keys != NULL);
    char strg[100];
    char *dataP;
    int loc, el, reTry, collisions = 0, found = 0;
    while (fgets(strg, 90, keys) != NULL)
    {
        el = strlen(strg) - 1;
        strg[el - 1] = '\0';
        dataP = malloc(strlen(strg) + 1);
        assert(dataP != NULL);
        strcpy(dataP, strg);
        reTry = 0;
        loc = divisionHash(goldenMultiplicative(makeNumber(strg)), reTry);
        while (table[loc] != NULL)
        {
            if (strcmp(table[loc], strg) == 0)
            {
                //printf("%s found.\n", strg);
                found++;
                break;
            }
            else
            {
                reTry++;
                collisions++;
            }
            loc = divisionHash(goldenMultiplicative(makeNumber(strg)), reTry);
        }
    }
    printf("Total collisions while searching %d\n", collisions);
    printf("Total word found %d\n", found);
}

int main(void)
{
    FILE *collection = fopen("collection", "r");
    assert(collection != NULL);
    char strg[100];
    char *dataP;
    int loc, collisions = 0, noCollisions = 0;
    int el, reTry, rehash, filled=0;
    initialise(TBLSZ);
    while (fgets(strg, 90, collection) != NULL)
    {
        el = strlen(strg) - 1;
        strg[el - 1] = '\0';
        dataP = malloc(strlen(strg) + 1);
        assert(dataP != NULL);
        strcpy(dataP, strg);
        reTry = 0;
        while (reTry < 100)
        {
            loc = divisionHash(goldenMultiplicative(makeNumber(strg)), reTry);
            if (table[loc] != NULL)
            {
                reTry++;
                collisions++;
                continue;
            }
            else
            {
                filled++;
                table[loc] = dataP;
                break;
            }
        }
    }
    printf("Total collisions %d\n", collisions);
    printf("Unused %d\n", TBLSZ - filled);
    printf("Filled %d\n", filled);
    search();
    return 0;
}