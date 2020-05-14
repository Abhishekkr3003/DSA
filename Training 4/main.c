#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"
char tmp[101];
int rollDice()
{
    int i = 1 + rand() % 6;
    return i;
}
int main(void)
{
    char *name;
    int dice;
    initDList();
    FILE *playerF = fopen("players.txt", "r");
    assert(playerF != NULL); // File is open

    ;
    while (fgets(tmp, 100, playerF)!=NULL)
    {
        // Get space filled with \0
        name = (char *)calloc(1, strlen(tmp) + 1);
        // Newline should not copied
        strncpy(name, tmp, strlen(tmp)-1);
        insertChair(name);
        printf("Added %s\n", name);
        //fgets(tmp, 100, playerF);
    }

    printf("\nAll palyers are in their chairs now. Game begins\n\n");

    while (!isEmpty())
    {
        printf("%s is in chair 0. ", whoInChair(0));
        dice = rollDice();
        if (dice % 2 == 1) // Odd numbers on left!
            dice *= -1;
        printf("\n\tRid chair %d.\t", dice);
        name = removeChair(dice);
        if (isEmpty())
            printf("\n\nWinner is %s\n", name);
        else
            printf("\tLosing player was %s.\n", name);
        free(name);
    }
    /*int ch, pos;
    while (1)
    {
        printf("1: INSERT\n2: DELETE\n3: PEEK\n4: Display\n5: EXIT\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            name = (char *)calloc(1, strlen(tmp) + 1);
            printf("Enter the name to be inserted\n");
            scanf(" %s", name);
            insertChair(name);
            break;
        case 2:
            printf("Enter position for deletion: ");
            scanf("%d", &pos);
            printf("Element deleted is %s\n", removeChair(pos));
            break;
        case 3:
            printf("Enter position to peek: ");
            scanf("%d", &pos);
            printf("Element peeked is %s\n", whoInChair(pos));
            break;
        case 4:
            Display();
            break;
        case 5:
            exit(1);
        default:
            printf("Wrong choice entered!!!\nEnter Again:\n");
            break;
        }
    }*/
    return 0;
}