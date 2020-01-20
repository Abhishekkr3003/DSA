/* An implementation of Deque  */
#include "deque.h"

int data[SIZE];
int left = -1;
int right = -1;

int insertLeft(int d)
{
	if (size() == SIZE - 1)
		return 0;
	if (left == -1)
	{
		left = right = 0;
		data[left] = d;
		return 0;
	}
	left = (left - 1 + SIZE) % SIZE;
	data[left] = d;
	return 0;
}

void insertRight(int d)
{
	if (size() == SIZE)
		exit(0);
	if (left == -1)
	{
		left = right = 0;
		data[left] = d;
	}
	else
	{
		right = (right + 1) % SIZE;
		data[right] = d;
	}
}

int removeLeft()
{
	int d, s;
	s = size();
	if (s == 0)
		return ERR_DATA;
	d = data[left];
	if (s == 1)
	{
		init();
		return d;
	}
	else
	{
		left = (left + 1) % SIZE;
		return d;
	}
}

int removeRight()
{
	int d, s;

	s = size();

	if (s == 0)
		return ERR_DATA; // Error value
	d = data[right];
	right = (right - 1 + SIZE) % SIZE;
	if (s == 1)
		init();
	return d;
}

int hasWelcome()
{
	return size() < SIZE;
}

int isEmpty()
{
	return size() == 0;
}

void init()
{
	left = right = -1;
}

int size()
{
	if (left == -1)
		return 0;
	return (right + SIZE - left) % SIZE + 1;
}
