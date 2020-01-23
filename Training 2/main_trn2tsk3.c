#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main(void)
{
    int i, s, item;
    init(); // Start deque

    for (i = 0; i < 10; i++)
    {
        insertLeft(i * i);
        s = size();
        printf("Size = %d Data = %d\n", s, removeRight());
        insertLeft(i * i * i);
    }

    while (size() > 0)
    {
        printf("Emptying deque %d\n", removeRight());
    }

    while (1)
    {
        printf("CHOICES:\n");
        printf("1. Insert at LEFT.\n2. Insert at RIGHT.\n3. Delete from LEFT.\n4. Delete from RIGHT.\n5. ...QUIT...\n");
        scanf("%d", &s);
        switch (s)
        {
        case 1:
            printf("Enter the number to be inserted : ");
            scanf("%d", &item);
            insertLeft(item);
            break;
        case 2:
            printf("Enter the number to be inserted : ");
            scanf("%d", &item);
            insertRight(item);
            break;
        case 3:
            item = removeLeft();
            printf("Deleted element is %d.\n", item);
            break;
        case 4:
            item = removeRight();
            printf("Deleted element is %d.\n", item);
            break;
        case 5:
            exit(0);
        default:
            printf("WRONG INPUT!!!\n");
        }
    }

    return 0;
}