all:
	flex lexical.l
	bison -dv syntax.y
	gcc -g main.c syntax.tab.c syntaxtree.c ao.h -lfl -o parser

.PHONY=run

wrong:
	./parser test1.c

right:
	./parser test2.c

debug:
	./parser test3.c -debug
