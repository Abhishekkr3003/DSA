/* An implementation of Deque  */
#include "deque.h"
#include<stdlib.h>
#include<stdio.h>

int data[SIZE];
int left = 8;
int right = 9;

int insertLeft(int d)
{
	if (size() == SIZE - 1)
    {
        printf("Element cannot be inserted as Deque is FULL!!!\n");
        return 0;
    }
    data[left] = d;
	left = (left - 1 + SIZE) % SIZE;
	return 0;
}

void insertRight(int d)
{
	if (size() == SIZE-1)
    {
		printf("Element cannot be inserted as Deque is FULL!!!\n");
        return;
    }
	data[right] = d;
    right = (right + 1) % SIZE;
}

int removeLeft()
{
	int d, s;
	s = size();
	if (s == 0)
	{
        printf("Nothing to delete from the deque.\n");
        return ERR_DATA;
    }
    left = (left + 1) % SIZE;
	d = data[left];
}

int removeRight()
{
	int d, s;
    s = size();
    if (s == 0)
	{
        printf("Nothing to delete from the deque.\n");
        return ERR_DATA;
    }
    right = (right - 1 + SIZE) % SIZE;
	d = data[right];
}

int isEmpty()
{
	return size() == 0;
}

void init()
{
	left = 8;
    right=9;
}

int size()
{
	if (right==(left+1)%SIZE)
		return 0;
	return ((right + SIZE - left-1) % SIZE);
}