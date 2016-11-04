#include <stdio.h>

extern FILE* yyin;
extern int yyparse(void);
extern int yyerror(char *);

int main(int argc, char *argv[]){
	if (!(yyin = fopen(argv[1], "r"))) {
		perror(argv[1]);
		return 1;
	}
	yyparse();
	return 0;
}
