#include "dequeGood.h"

/* storage allocated here */
struct node hdr;

/* ADT interface functions */
/* THink of hdr as if it is on top 
of all member nodes of deque.
Left and right of header is not symmetric to
those of member nodes */

void init()
{
	// unused
	hdr.data = 0;
	hdr.nextL = hdr.nextR = NULL;
}

void joinL(int d)
{
	struct node *new = (struct node *)malloc(sizeof(struct node));
	assert(new != NULL); // Stop if problem

	new->data = d;

	if (hdr.nextL == NULL)
	{
		assert(hdr.nextR == NULL);
		hdr.nextL = hdr.nextR = new;
		new->nextL = new->nextR = NULL;
		return;
	}

	assert(hdr.nextR != NULL);
	assert(hdr.nextL->nextL == NULL);
	hdr.nextL->nextL = new;
	new->nextR = hdr.nextL;
	new->nextL = NULL;
	hdr.nextL = new;
}

void joinR(int d)
{
	struct node *new = (struct node *)malloc(sizeof(struct node));
	assert(new != NULL); // Stop if problem

	new->data = d;

	if (hdr.nextL == NULL)
	{
		assert(hdr.nextR == NULL);
		hdr.nextL = hdr.nextR = new;
		new->nextL = new->nextR = NULL;
		return;
	}

	assert(hdr.nextR != NULL);
	assert(hdr.nextL->nextL == NULL);
	new->nextR = NULL;
	new->nextL = hdr.nextR;
	hdr.nextR->nextR = new;
	hdr.nextR = new;
}

int leaveL()
{
	struct node *tmp;
	assert(hdr.nextL != NULL && hdr.nextR != NULL);
	int d = hdr.nextL->data;
	tmp = hdr.nextL;
	assert(tmp->nextL == NULL);
	if (tmp->nextR == NULL)
	{
		hdr.nextL = hdr.nextR = NULL;
		free(tmp);
		return d;
	}

	tmp->nextR->nextL = NULL;
	hdr.nextL = tmp->nextR;
	free(tmp);
	return d;
}

int leaveR()
{
	struct node *tmp;
	assert(hdr.nextL != NULL && hdr.nextR != NULL);
	int d = hdr.nextR->data;
	tmp = hdr.nextR->nextL;
	if (tmp != NULL)
		tmp->nextR = NULL;
	free(hdr.nextR);
	hdr.nextR = tmp;
	if (tmp == NULL)
		hdr.nextL = NULL;
	assert(tmp != NULL || hdr.nextL == NULL);
	return d;
}

int size()
{
	int i = 0;
	struct node *ptr = hdr.nextL;

	while (ptr != NULL)
	{
		i++;
		ptr = ptr->nextR;
	}
	return i;
}