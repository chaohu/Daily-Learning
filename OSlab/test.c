#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

void waiting(),stop();
int wait_mark;

void waiting()
{
      while(wait_mark!=0);
}

void stop()
{
     wait_mark=0;
}

int main()
{
    int p1;
    while((p1= fork()) == -1);
    if (p1>0)
    {
        wait_mark=1;
        signal(SIGINT,stop); 
        waiting(); 
        kill(p1,SIGUSR1);
        wait(0);
        printf("parent process is killed!\n");
        exit(0);
    }
    else
    {
        wait_mark=1;
        signal(SIGUSR1,stop);
        signal(SIGINT,SIG_IGN);
        waiting();
        printf("child process1 is killed by parent!\n");
        exit(0);
    }
}
