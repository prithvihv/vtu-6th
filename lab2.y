%{
#include <stdio.h>
#include <stdlib.h>
int count=0,n;
%}
%token A
%token B
%%
S : X B | {if(n==count){printf("correct bro");}else{printf("wrong bro ");}}
X : A X |T
T : A {count++;};
%%
int yyerror(){
    printf("invalid String");
    return 0;
}

int main(){
    printf("yeno:");
    scanf("%d",&n);
    printf("exp:");
    yyparse();
    printf("valid String");
}