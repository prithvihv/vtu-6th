yacc -d lab6b.y
lex lab6b.l
cc y.tab.c lex.yy.c -ll -o .comp.out
./.comp.out