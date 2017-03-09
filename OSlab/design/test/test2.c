#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	char sourcefile[30] = "task1.c";
    char destfile[30] = "hehe.c";
    int i;
	int source = open(sourcefile,O_RDONLY,0);
	int dest = open(destfile,O_WRONLY|O_CREAT|O_TRUNC,0600);
	char buf[4096];
	if(source > 0 && dest > 0) {
		do {
			i = read(source,buf,4096);
			write(dest,buf,i);
		}
		while(i);
	}
	else {
		printf("Error!");
	}
	close(source);
	close(dest);
	return 10;
}
