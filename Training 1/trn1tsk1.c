#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LPAR '('
#define RPAR ')'
#define PLUS '+'
#define MULT '*'
#define MOD '%'
#define FINISH '\0'
#define INT '0'

struct token
{
    char kind;
    int value;
};

char expr[100];
int where = 0;

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

int main()
{
    struct token token;
    int i;
    printf("Input expression:");
    fgets(expr, 99, stdin);
    token = getNextToken();
    while (token.kind != FINISH)
    {
        printf("%c", token.kind);
        if (token.kind == INT)
            printf(" %d", token.value);
        printf("\n");
        token = getNextToken();
    }
    return 0;
}