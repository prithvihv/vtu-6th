%{
#include <stdio.h>
int count=0;
%}
%%
"/*"[^/*]*"*/" {count++;}
"//" {count++;}
%%
int main(int argc,char **argv){
    printf("hello world");
    yyin = fopen(argv[0],"r");
    yyout = fopen(argv[1],"w");
    yylex();
    printf("numberOf Lines %d",count);
}