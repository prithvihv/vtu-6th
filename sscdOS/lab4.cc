#include <stdio.h>
#include <string.h>
#include <conio.h>
int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];
void check();
void main()
{
    puts("GRAMMAR is E->E+T|T \n T->T*F|F \n F->(E)|E->id\n ");
    puts("enter input string ");
    gets(a);
    c = strlen(a);
    strcpy(act, "SHIFT->");
    puts("stack \t input \t action");
    for (k = 0, i = 0; j < c; k++, i++, j++)
    {
        if (a[j] == 'i' && a[j + 1] == 'd')
        {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, a, act);
            check();
        }
        else
        {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act);
        }
    }
    getch();
}
void check()
{
    for (z = 0; z < c; z++)
        if (stk[z] == 'i' && stk[z + 1] == 'd')
        {
            stk[z] = 'F';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO F", stk, a);
            j++;
        }
    for (z = 0; z < c; z++)
        if (stk[z] == 'T' && stk[z + 1] == '*' && stk[z + 2] == 'F')
        {
            stk[z] = 'T';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO T", stk, a);
            i = i - 2;
            check();
        }
    for (z = 0; z < c; z++)
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'T' && a[j + 1] != '*')
        {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO E", stk, a);
            i = i - 2;
            check();
        }
    for (z = 0; z < c; z++)
    {
        if (stk[z] == 'T' && a[j + 1] == '*')
        {
            return;
        }
        else if ((stk[z] == 'T' && a[j + 1] != '\0') || stk[0] == 'T')
        {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO E", stk, a);
            check();
        }
    }
    for (z = 0; z < c; z++)
        if (stk[z] == 'F')
        {
            stk[z] = 'T';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO T", stk, a);
            check();
        }
    for (z = 0; z < c; z++)
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')')
        {
            stk[z] = 'F';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO F", stk, a);
            i = i - 2;
            check();
        }
}
