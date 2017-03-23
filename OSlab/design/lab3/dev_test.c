#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	int fp;
	char w_buf1[11] = "U201414815";
	char w_buf2[11] = "abcdefg";
	char r_buf1[50];
	char r_buf2[20];
	
	if((fp = open("/dev/mydev0",O_RDWR)) == -1) {
		perror("fopen");
		exit(1);
	}
	if((write(fp,w_buf1,10)) == -1) {
		perror("write");
		exit(1);
	}
	if((write(fp,w_buf2,11)) == -1) {
		perror("write");
		exit(1);
	}
	if((read(fp,r_buf1,10)) == -1) {
		perror("read");
		exit(1);
	}
	if((read(fp,r_buf2,2)) == -1) {
		perror("read");
		exit(1);
	}
	r_buf1[10] = '\0';
	printf("%s\n",r_buf1);
	r_buf2[2] = '\0';
	printf("%s\n",r_buf2);
	close(fp);
	return 0;
}
