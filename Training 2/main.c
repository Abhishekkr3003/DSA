#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main(void)
{
	int i;
	init(); // Start deque

	for (i = 0; i < 10; i++)
	{
		insertLeft(i * i);
		printf("Size = %d Data = %d\n", size(), removeRight());
		insertLeft(i * i * i);
	}

	while (size() > 0)
	{
		printf("Emptying deque %d\n", removeRight());
	}

	return 0;
}
