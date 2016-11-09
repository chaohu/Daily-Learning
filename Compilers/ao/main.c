#include "ao.h"

int main(int argc, char *argv[]){
	if (argc >= 3) {
		if (strcmp(argv[2], "-debug") == 0) {
			printf("debugging activated\n");
			yydebug = 1;
		}
	}
	if (!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
       	return 1;
	}
	yyparse();
	return 0;
}
