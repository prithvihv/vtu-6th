yacc -d lab2.y
lex lab2.l
cc y.tab.c lex.yy.c -ll -o .comp.out
./.comp.out