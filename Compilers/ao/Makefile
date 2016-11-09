all:
	flex lexical.l
	bison -dv syntax.y
	gcc -g main.c syntax.tab.c syntaxtree.c ao.h -lfl -o parser

.PHONY=run

run:
	./parser test.c

debug:
	./parser test.c -debug
