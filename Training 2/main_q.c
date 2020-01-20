#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void)
{
    int i, n;
    while (1)
    {
        printf("To INSERT press 1.\nTo REMOVE press 2.\nTo EXIT press 3.\n");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            printf("Enter the element : ");
            scanf("%d", &n);
            joinQ(n);
            break;
        case 2:
            n = leaveQ();
            printf("Element removed is %d.\n", n);
            break;
        case 3:
            exit(0);
        default:
            printf("WRONG INPUT ENTERED!!!\n");
            break;
        }
    }
    /*for (i = 0; i < 10; i++)
    {
        joinQ(i * i);
        printf("Data = %d\n", leaveQ());
        joinQ(i * i * i);
    }

    while (!isEmpty())
    {
        printf("Emptying queue %d\n", leaveQ());
    }

    return 0;*/
}
