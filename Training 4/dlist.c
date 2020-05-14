#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dlist.h"

struct chair *pointAtChair0;

void initDList()
{
    pointAtChair0 = NULL;
}

void insertChair(char *player)
{
    struct chair *temp;
    temp = (struct chair *)malloc(sizeof(struct chair));
    assert(temp != NULL);

    temp->player = player;

    if (isEmpty())
    {
        temp->leftChair = temp->rightChair = pointAtChair0 = temp;
        return;
    }

    temp->rightChair = pointAtChair0;
    temp->leftChair = pointAtChair0->leftChair;
    if (pointAtChair0->rightChair == pointAtChair0)
        pointAtChair0->rightChair = temp;
    else
        pointAtChair0->leftChair->rightChair = temp;
    pointAtChair0->leftChair = temp;
}

char *removeChair(int displacement)
{
    assert(!isEmpty());
    char *player;
    struct chair *ptr = pointAtChair0;
    if (displacement > 0)
    {
        for (int i = 0; i < displacement; i++)
            ptr = ptr->rightChair;

        assert(ptr->player != NULL);
        player = ptr->player;

        if (pointAtChair0->rightChair == pointAtChair0 && pointAtChair0->leftChair == pointAtChair0)
            printf("Freeing last chair.\n");
        else if (pointAtChair0->rightChair->rightChair == pointAtChair0)
            printf("Freeing second last chair.\n");
        else if (ptr == pointAtChair0)
            printf("Freeing chair 0.\n");
        else
            printf("Freeing a chair; at least 2 chairs left.\n");

        if (ptr->rightChair == ptr && ptr->leftChair == ptr)
        {
            initDList();
            free(ptr);
            return player;
        }

        ptr->leftChair->rightChair = ptr->rightChair;
        ptr->rightChair->leftChair = ptr->leftChair;
        if (ptr == pointAtChair0)
            pointAtChair0 = ptr->rightChair;

        free(ptr);
        return player;
    }
    else
    {
        for (int i = 0; i > displacement; i--)
            ptr = ptr->leftChair;

        assert(ptr->player != NULL);
        player = ptr->player;

        if (pointAtChair0->rightChair == pointAtChair0 && pointAtChair0->leftChair == pointAtChair0)
            printf("Freeing last chair.\n");
        else if (pointAtChair0->rightChair->rightChair == pointAtChair0)
            printf("Freeing second last chair.\n");
        else if (ptr == pointAtChair0)
            printf("Freeing chair 0.\n");
        else
            printf("Freeing a chair; at least 2 chairs left.\n");

        if (ptr->rightChair == ptr && ptr->leftChair == ptr)
        {
            initDList();
            free(ptr);
            return player;
        }

        ptr->leftChair->rightChair = ptr->rightChair;
        ptr->rightChair->leftChair = ptr->leftChair;

        if (ptr == pointAtChair0)
            pointAtChair0 = ptr->leftChair;

        free(ptr);
        return player;
    }
}

char *whoInChair(int displacement)
{
    if (isEmpty())
        return "None found";
    struct chair *ptr = pointAtChair0;
    if (displacement > 0)
    {
        for (int i = 0; i < displacement; i++)
            ptr = ptr->rightChair;
        return ptr->player;
    }
    else
    {
        for (int i = 0; i > displacement; i--)
            ptr = ptr->leftChair;
        return ptr->player;
    }
}

int isEmpty()
{
    if (pointAtChair0 == NULL)
        return 1;
    else
        return 0;
}

void Display()
{
    int i = 1;
    struct chair *ptr = pointAtChair0;
    do
    {
        printf("%d-> %s\n", i, ptr->player);
        i++;
        ptr = ptr->rightChair;
    } while (ptr != pointAtChair0);
    ptr = pointAtChair0;
    i = 1;
    do
    {
        printf("%d-> %s\n", i, ptr->player);
        i++;
        ptr = ptr->leftChair;
    } while (ptr != pointAtChair0);
}