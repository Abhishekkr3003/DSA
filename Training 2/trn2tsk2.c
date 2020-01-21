#include <stdio.h>
#include "queue.h"

int main()
{
    int i, num1 = 0, num2 = 0, count = 0;
    for (i = 2; i <= 100000; i++)
        joinQ(i);
    joinQ(-1);
    while (1)
    {
        num1 = leaveQ();
        if (num1 == -1)
            break;
        while (1)
        {
            num2 = leaveQ();
            if (num2 == -1)
                break;

            if (num2 % num1 != 0)
            {
                joinQ(num2);
            }
        }
        joinQ(-1);
        printf("%d ", num1);
        count++;
    }
    printf("\n");
    printf("There are %d prime numbers between 2 and 100000.\n", count);

    return 0;
}