%{
#include <stdio.h>
int count=0;
%}
%%
"/*"[^/*]*"*/" {count++;}
"//".* {count++;}
%%
int main(int argc,char **argv){
    printf("hello world");
    yyin = fopen(argv[1],"r");
    yyout = fopen(argv[2],"w");
    yylex();
    printf("numberOf Lines %d",count);
}