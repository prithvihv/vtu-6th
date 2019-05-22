%{
#include <stdio.h>
int barkets , flag ,num,op;
%}
%%
[0-9]+ {num++;}
[+-/*] {op++;}
"(" {barkets++;}
")" {barkets--;}
%%
int main(){
    printf("Enter expression:");
    yylex();
    if(barkets==0&&(op+1)==num){
        printf("correct shit \n");
    }else{
        printf("wrong shit \n");
    }
}
int yywrap(){
    return 1;
}