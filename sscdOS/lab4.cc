#include <stdio.h>
#include <string.h>
#include <curses.h>
int k = 0, z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];
void check();
int main()
{
    puts("GRAMMAR is E->E+T|T \n T->T*F|F \n F->(E)|E->id\n ");
    puts("enter input string ");
    scanf("%s", &a);
    c = strlen(a);
    strcpy(act, "SHIFT->");
    puts("stack \t input \t action");
    for (k = 0, i = 0, j = 0; j < c; k++, i++, j++)
    {
        if (a[j] == 'i' && a[j + 1] == 'd') // if id then =>
        {
            stk[i] = a[j]; // move id to stack
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' '; // clear id from input
            a[j + 1] = ' ';
            printf("\n$%s\t%s$\t%sid", stk, a, act);
            check();
        }
        else // else operation
        {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act);
        }
    }
    return 0;
}
void check()
{
    for (z = 0; z < c; z++)
        if (stk[z] == 'i' && stk[z + 1] == 'd') // id on the stack
        {
            stk[z] = 'F';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO F", stk, a);
            j++; // does'nt need to check again
        }
    for (z = 0; z < c; z++)
        if (stk[z] == 'T' && stk[z + 1] == '*' && stk[z + 2] == 'F') // T*F on the stack
        {
            stk[z] = 'T';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO T", stk, a);
            i = i - 2;
            check();
        }
    for (z = 0; z < c; z++)
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'T' && a[j + 1] != '*') // E+T & * is not input
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
        if (stk[z] == 'T' && a[j + 1] == '*') // T is stack & * is input
        {
            return;
        }
        else if ((stk[z] == 'T' && a[j + 1] != '\0') || stk[0] == 'T') // T at top || T at bottom
        {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO E", stk, a);
            check();
        }
    }
    for (z = 0; z < c; z++)
        if (stk[z] == 'F') // F on stack
        {
            stk[z] = 'T';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO T", stk, a);
            check();
        }
    for (z = 0; z < c; z++)
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') // (E) on stack
        {
            stk[z] = 'F';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\tREDUCE TO F", stk, a);
            i = i - 2;
            check();
        }
}
