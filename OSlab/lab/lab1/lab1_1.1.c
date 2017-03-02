#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void waiting();
void stop();
int wait_mark;

void waiting() {
    while(wait_mark != 0);
}

void stop(int sig_no) {
    if(sig_no == SIGINT) wait_mark = 0;
    if(sig_no == SIGUSR1) wait_mark = 0;
    if(sig_no == SIGUSR2) wait_mark = 0;
}

int main(void) {
    int fd[2];
    int child1pid,child2pid;
    char readbuffer[80];
    
    pipe(fd);
    if(((child1pid = fork()) == -1) || ((child2pid = fork()) == -1)) {    //创建子进程1
        perror("fork");
        exit(1);
    }

    if(child1pid == 0) {    //子进程1运行代码
        signal(SIGUSR1,stop);
        signal(SIGINT,SIG_IGN);
        wait_mark = 1;
        int num = 1;
        char cnum[5];
        char string1[20] = "I send you ";
        char string2[10] = " times.\n";
        char *string = (char *)malloc(sizeof(char)*40); 
        close(fd[0]);
        while(wait_mark) {
            sprintf(cnum,"%d",num);
            strcat(string,string1);
            strcat(string,cnum);
            strcat(string,string2);
            write(fd[1],string,(strlen(string)+1));
            free(string);
            string = (char *)malloc(sizeof(char)*40); 
            num++;
            sleep(1);
        }
        printf("Child Process 1 is Killed by Parent!\n");
        exit(0);
    }
    else if(child2pid == 0) {   //子进程2运行代码
            signal(SIGUSR2,stop);
            signal(SIGINT,SIG_IGN);
            wait_mark = 1;
            close(fd[1]);
            while(wait_mark) {
            sleep(1);
            read(fd[0],readbuffer,sizeof(readbuffer));
            printf("Received string:%s",readbuffer);
            }
            printf("Child Process 2 is Killed by Parent!\n");
            exit(0);
    }
    else {  //父进程代码
            signal(SIGINT,stop);
            wait_mark = 1;
            waiting();
            kill(child1pid,SIGUSR1);
            kill(child2pid,SIGUSR2);
            waitpid(child1pid,NULL,0);
            waitpid(child2pid,NULL,0);
            close(fd[0]);
            close(fd[1]);
            printf("Parent Process is Killed!\n");
            exit(0);
    }
    return 0;
}
