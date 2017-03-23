#ifndef task4
#define task4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include <time.h>

GtkWidget *clist;

time_t times;
struct tm *lmodifytime;
char buf_time[50];


typedef struct {
    char name[256]; //进程名称
	char pid[20];
	char state[20];
    char vmsize[20];     //虚拟内存信息
	char priority[20];
	char ppid[20];
}proc_info_st;      //保存读取的进程信息

#define PROC_NAME_LINE 1    //名称所在行
#define PROC_PID_LINE 5     //pid所在行
#define PROC_STATE_LINE 2
#define PROC_VMSIZE_LINE 17 //虚拟内存所在行


gint CPU_Refresh(gpointer label);
char *CPU_UseRate();

gint MEM_Refresh(gpointer label);
char *MEM_UseRate();

//读取进程信息
gint get_proc(gpointer vbox);
void read_proc(proc_info_st *info,const char *c_pid,gpointer clist);
int read_line(FILE *fp,char *buff,int buff_len,int line);


//内存利用率
gint Mem_UseRate(gpointer label);

gint SYS_Refresh(gpointer label);
gint show_time(gpointer label);

#endif
