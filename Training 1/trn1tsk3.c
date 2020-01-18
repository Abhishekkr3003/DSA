#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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

char infix[100];
char expr[100];
char temp[2];
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
int incoming_priority(char);
int in_stack_priority(char);

void main()
{
    struct token token;
    char ch;
    printf("Input expression: ");
    fgets(infix, 99, stdin);
    initstack();
    token = getNextToken();
    while (token.kind != FINISH)
    {
        if (token.kind == INT)
        {
            sprintf(temp, "%d", token.value);
            strcat(expr, temp);
            strcat(expr, " ");
        }

        else
        {
            if (token.kind == '(')
                push(token.kind);
            else if (token.kind == ')')
            {
                ch = peek();
                while (!isEmpty() && ch != '(')
                {
                    ch = pop();
                    sprintf(temp, "%c", ch);
                    strcat(expr, temp);
                    strcat(expr, " ");
                    ch = peek();
                }
                ch = pop();
            }
            else
            {
                if (isEmpty())
                    push(token.kind);
                else
                {
                    ch = peek();
                    if (ch == '(' || incoming_priority(token.kind) > in_stack_priority(ch))
                    {
                        push(token.kind);
                    }
                    else
                    {
                        while (!isEmpty() && ch != '(' && incoming_priority(token.kind) <= in_stack_priority(ch))
                        {
                            ch = pop();
                            sprintf(temp, "%c", ch);
                            strcat(expr, temp);
                            strcat(expr, " ");
                            if (!isEmpty())
                                ch = peek();
                        }
                        push(token.kind);
                    }
                }
            }
        }
        token = getNextToken();
    }
    while (!isEmpty())
    {
        sprintf(temp, "%c", pop());
        strcat(expr, temp);
        strcat(expr, " ");
    }
    printf("%s\n", expr);
}

void skipWhite()
{
    while (isspace(infix[where]))
        where++;
}

void skipDigits()
{
    while (isdigit(infix[where]))
        where++;
}

struct token getNextToken()
{
    struct token token;
    skipWhite();

    if (isdigit(infix[where]))
    {
        sscanf(&infix[where], "%d", &token.value);
        token.kind = INT;
        skipDigits();
    }
    else
    {
        token.kind = infix[where];
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
    if (!isEmpty())
        return top->info;
    else
    {
        printf("THE STACK IS EMPTY!!!\n");
        exit(0);
    }
}

int incoming_priority(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    else if (ch == '^')
        return 3;
    else
    {
        printf("-->UNKNOWN CHARACTER ENTERED!!!\n");
        exit(0);
    }
}

int in_stack_priority(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    else if (ch == '^')
        return 4;
    else
    {
        printf("\nUNKNOWN CHARACTER ENTERED!!!\n");
        exit(0);
    }
}