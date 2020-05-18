#include "expr.h"
#include <stdio.h>
#include <stdlib.h>

/* Gives pointer to the first term in the expression list */
struct term *getFirstTerm(expression *ptrToExpr)
{
    assert(ptrToExpr != NULL);
    assert(*ptrToExpr != NULL);
    return (*ptrToExpr)->nextP;
}
/* Initialise a expression with no term */
void createExpr(expression *ptrToExpr)
{
    assert(ptrToExpr != NULL);
    (*ptrToExpr) = malloc(sizeof(struct term));
    (*ptrToExpr)->nextP = NULL;
}
/* Insert a new term in expression list -- term with power should not exist
*/
void insertTerm(expression *ptrToExpr, int coeff, int power)
{
    struct term *ptr, *prev;
    struct term *newTerm = malloc(sizeof(struct term));
    newTerm->coeff = coeff;
    newTerm->power = power;
    ptr = getFirstTerm(ptrToExpr);
    prev = *ptrToExpr;
    /* Notice that ptr is used only if not NULL */
    while (ptr != NULL && power < ptr->power)
    {
        // Find the right location for new node
        prev = ptr;
        ptr = getNextTerm(ptrToExpr, ptr);
    }
    assert(ptr == NULL || ptr->power != power);
    newTerm->nextP = ptr;
    prev->nextP = newTerm;
}
/* Gives next term in the expression after one referenced by termP */
struct term *getNextTerm(expression *ptrToExpr, struct term *termP)
{
    assert(termP != NULL);
    return termP->nextP;
}
/* Available here but not through expr.h */
static void printTerm(struct term *term)
{
    printf("%+d*X^%d ", term->coeff, term->power);
}
/* Prints the expression */
void printExpr(expression *ptrToExpr)
{
    struct term *prnt = getFirstTerm(ptrToExpr);
    while (prnt != NULL)
    {
        printTerm(prnt);
        prnt = getNextTerm(ptrToExpr, prnt);
    }
    printf("\n");
}

void addTerm(expression *prtToExpr, int coeff, int power)
{
    struct term *ptr, *prev, *term;
    ptr = getFirstTerm(prtToExpr);
    prev = *prtToExpr;
    while (ptr != NULL && power <= ptr->power)
    {
        if (ptr->power == power)
        {
            ptr->coeff += coeff;
            if (ptr->coeff == 0)
            {
                prev->nextP = ptr->nextP;
                free(ptr);
            }
            return;
        }
        prev = ptr;
        ptr = getNextTerm(prtToExpr, ptr);
    }
    term=(struct term *)malloc(sizeof(struct term));
    term->coeff = coeff;
    term->power = power;
    term->nextP = ptr;
    prev->nextP = term;
}

struct term *searchTerm(expression *prtToExpr, int pow)
{
    struct term *term;
    term = getFirstTerm(prtToExpr);
    assert(term != NULL);
    while (term != NULL && pow <= term->power)
    {
        if (term->power == pow)
        {
            printf("Term with power %d found.\n", pow);
            return term;
        }
        term = getNextTerm(prtToExpr, term);
    }
    printf("Term with power %d not found.\n", pow);
    return NULL;
}

void makeExprCopy(expression *srcExpr, expression *dstExpr)
{
    struct term *term = getFirstTerm(srcExpr);
    assert(term != NULL);
    while (term != NULL)
    {
        addTerm(dstExpr, term->coeff, term->power);
        term = getNextTerm(srcExpr,term);
    }
}