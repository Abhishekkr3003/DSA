#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct node
{
    int info;
    struct node *link;
} node;
node *top;

struct token
{
    char kind;
    int value;
};

#define LPAR '('
#define RPAR ')'
#define PLUS '+'
#define MULT '*'
#define MOD '%'
#define FINISH '\0'
#define INT '0'

char expr[100];
int where = 0;

void skipWhite();
void skipDigits();
struct token getNextToken();

void push(int);
int pop();
int isEmpty();
int isfull(node *);
int peek();
void initstack();

void main()
{
    struct token token;
    int i, a, b;
    char ch;
    printf("Input expression: ");
    fgets(expr, 99, stdin);
    token = getNextToken();
    while (token.kind != FINISH)
    {
        if (token.kind == INT)
            push(token.value);
        else
        {
            a = pop();
            b = pop();
            switch (token.kind)
            {
            case '+':
                push(a + b);
                break;
            case '-':
                push(b - a);
                break;
            case '*':
                push(b * a);
                break;
            case '/':
                push(b / a);
                break;
            case '%':
                push(b % a);
                break;
            case '^':
                push(pow(b, a));
                break;
            default:
                printf("WRONG POSTFIX ENTERED!!!\n");
                exit(0);
            }
        }
        token = getNextToken();
    }
    int solution;
    solution = pop();
    if (!isEmpty())
    {
        printf("WRONG POSTFIX ENTERED!!!\n");
        exit(0);
    }
    else
        printf("Solution of expresion is: %d\n", solution);
}

void skipWhite()
{
    while (isspace(expr[where]))
        where++;
}

void skipDigits()
{
    while (isdigit(expr[where]))
        where++;
}

struct token getNextToken()
{
    struct token token;
    skipWhite();

    if (isdigit(expr[where]))
    {
        sscanf(&expr[where], "%d", &token.value);
        token.kind = INT;
        skipDigits();
    }
    else
    {
        token.kind = expr[where];
        where++;
    }
    return token;
}

void push(int item)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    if (!isfull(temp))
    {
        temp->info = item;
        temp->link = top;
        top = temp;
    }
}

int pop()
{
    int item;
    if (!isEmpty())
    {
        node *temp;
        temp = top;
        item = temp->info;
        top = temp->link;
        free(temp);
        return item;
    }
    else
    {
        printf("WRONG POSTFIX ENTERED!!!\n");
        exit(0);
    }
}

int isEmpty()
{
    if (top == NULL)
        return 1;
    else
        return 0;
}

int isfull(node *temp)
{
    if (temp == NULL)
        return 1;
    else
        return 0;
}

void initstack()
{
    top = NULL;
}

int peek()
{
    return top->info;
}