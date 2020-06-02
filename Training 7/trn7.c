#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

char town[] = "VILL: RUPA KI NANGAL";

struct Huff
{
	int freq;
	char alpha;
	struct Huff *left;
	struct Huff *right;
	struct Huff *parent;
};

char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int freq[] = {21912, 16587, 14810, 14003, 13318, 12666, 11450, 10977, 10795, 7874, 7253, 5246, 4943, 4761, 4200, 3853, 3819, 3693, 3316, 2715, 2019, 1257, 315, 205, 188, 128};

//int freq[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
//int freq[] = {3, 0, 0, 0, 0, 0, 1, 0, 2, 0, 2, 3, 0, 2, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0};

struct Huff alphabet[26]; // External nodes of Huffman tree.
struct Huff *heap[30];

int heapSz = 0; // index 0 is not used in this heap

void heapifyUp(int index);
void heapifyDown(int index);
void initAlphaNodes(void)
{

	/* Fill freq data in array alphabet
	Alphabets are External nodes in
	our Huffman tree
	External nodes are declared in our code.
	*/

	int i;

	for (i = 0; i < 26; i++)
	{
		alphabet[i].alpha = letters[i];
		alphabet[i].freq = freq[i];
		alphabet[i].left = NULL;
		alphabet[i].right = NULL;
	}
}

struct Huff *makeHuffNode(int freq, struct Huff *left, struct Huff *right)
{
	struct Huff *newNode = malloc(sizeof(struct Huff));
	assert(newNode != NULL);
	newNode->alpha = ' '; // symbol marks internal node
	newNode->freq = freq;
	newNode->right = right;
	newNode->left = left;
	if (left != NULL)
	{
		left->parent = newNode;
		if (left->alpha == ' ')
			left->alpha = '0';
	}
	if (right != NULL)
	{
		right->parent = newNode;
		right->alpha = '1';
	}
	return newNode;
}

void addToHeap(struct Huff *newNode)
{
	assert(heapSz < 30);
	heap[++heapSz] = newNode;
	heapifyUp(heapSz); // Make the priority queue good
}

struct Huff *removeMin(void)
{
	assert(heapSz > 1);
	struct Huff *tmp = heap[1];
	heap[1] = heap[heapSz--];
	heapifyDown(1);
	return tmp;
}

void initExternalHeapNodes(void)
{
	int i;
	for (i = 0; i < 26; i++)
	{
		addToHeap(makeHuffNode(alphabet[i].freq, &alphabet[i], NULL));
	}
}

void swapAtIdx(int x, int y)
{
	/* Used by heapify functions */
	struct Huff *tmp;
	tmp = heap[x];
	heap[x] = heap[y];
	heap[y] = tmp;
}

void heapifyUp(int index)
{
	int par, i,j;
	for (j = 2; j <= index; j++)
	{
		i = j;
		par = i / 2;
		while (par != 0 && heap[par]->freq >= heap[i]->freq)
		{
			swapAtIdx(i, par);
			i = par;
			par = i / 2;
		}
	}
}

void heapifyDown(int parent)
{
	int left_child, right_child;
	left_child = 2 * parent;
	right_child = left_child + 1;
	
		if (left_child<=heapSz && heap[parent]->freq >= heap[left_child]->freq)
		{

			if (right_child<=heapSz && heap[left_child]->freq < heap[right_child]->freq|| right_child>heapSz )
			{
				swapAtIdx(parent, left_child);
				parent = left_child;
			}
			else if (heap[left_child]->freq >= heap[right_child]->freq && heap[parent]->freq >= heap[right_child]->freq)
			{
				swapAtIdx(parent, right_child);
				parent = right_child;
			}
			
		}
		else if (right_child <= heapSz && heap[right_child]->freq <= heap[parent]->freq)
		{
			swapAtIdx(parent, right_child);
			parent = right_child;
		}
		else
			return;
		heapifyDown(parent);	
}

int heapIsRootOnly(void)
{
	return heapSz == 1;
}
void emitLetterCode(char c)
{
	int i = c - 'A';
	struct Huff *bit = alphabet[i].parent;
	while (bit != NULL)
	{
		printf("%c", bit->alpha);
		bit = bit->parent;
	}
}

void initial_alphabet()
{
	struct Huff *temp;
	for (int i = 1; i < 27; i++)
	{
		temp = heap[i];
		assert(temp->left != NULL);
		printf("Alphabet: %c || Frequency: %d.\n", temp->left->alpha, temp->left->freq);
	}
}
// void print_alpha()
// {
// 	char cho[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
// 	printf("\n");
//  for (int i = 0; i < 26; i++)
// 	{
// 		printf("%c: ", cho[i]);
// 		emitLetterCode(cho[i]);
// 		printf("\n");
// 	}
// }

int main(void)
{
	struct Huff *left, *right, *newNode, *node;
	int i;
	initAlphaNodes();
	initExternalHeapNodes();
	//initial_alphabet();
	while (!heapIsRootOnly())
	{
		left = removeMin();
		if (heapIsRootOnly())
		{
			right = heap[1];
			heap[1] = makeHuffNode(left->freq + right->freq, left, right);
			break;
		}
		right = removeMin();
		addToHeap(makeHuffNode(left->freq + right->freq, left, right));
	}
	/* Code town */
	printf("Words in %s are coded as follows\n", town);
	i = -1;
	while (town[++i] != '\0')
	{
		if (isspace(town[i]))
			printf("\n");
		else if (!isupper(town[i]))
			printf("\n%c", town[i]);
		else
			emitLetterCode(town[i]);
	}
	printf("\n");
}
