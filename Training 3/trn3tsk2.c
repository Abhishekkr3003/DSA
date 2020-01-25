#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void main()
{
    FILE *fp;
    fp = fopen("copiedProgrami.c", "r");
    assert(fp != NULL);
    char ch;
    ch = fgetc(fp);
    while (!feof(fp))
    {
        printf("%c", ch);
        ch = fgetc(fp);
    }
    fclose(fp);
    printf("\n");
}