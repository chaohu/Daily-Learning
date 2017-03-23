#include "task4.h"

static int flag = 0;    			//计算CPU使用率时启动程序的标志
static float cpu_used_percent = 0;  //CPU使用率
static long idle,total;


/*
 * CPU利用率计算与显示
 */
gint CPU_Refresh(gpointer label) {
    gtk_label_set_text(label,CPU_UseRate());
	gtk_misc_set_alignment(GTK_MISC(label),0.5,0);
	gtk_widget_show(label);
    return TRUE;
}

char *CPU_UseRate() {
	char *temp_cpu;
	temp_cpu = (char *)malloc(sizeof(char) * 50);
	long user_t,nice_t,system_t,idle_t,total_t;	//此次读取的数据
	long total_c,idle_c;	//此次数据与上次数据的差
	char cpu_t[10],buffer[71];
	FILE *fp;
	fp = fopen("/proc/stat","r");
	if(fp == NULL) {
		perror("fopen");
		exit(1);
	}
	fgets(buffer,70,fp);
	fclose(fp);
	sscanf(buffer, "%s %ld %ld %ld %ld",cpu_t, &user_t, &nice_t, &system_t, &idle_t);
	
	if(flag == 0) {
		flag = 1;
		idle = idle_t;
		total = user_t + nice_t + system_t + idle_t;
		cpu_used_percent = 0;
	}
	else {
		total_t = user_t + nice_t + system_t + idle_t;
		total_c = total_t - total;
		idle_c = idle_t - idle;
		cpu_used_percent = (100.0 * (total_c - idle_c)) / total_c;
		total = total_t;	//此次数据保存
		idle = idle_t;
	}
	sprintf(temp_cpu,"cpu使用率:\t%0.1f%%",cpu_used_percent);
	return temp_cpu;
}


/*
 * MEM利用率计算与显示
 */
gint MEM_Refresh(gpointer label) {
    gtk_label_set_text(label,MEM_UseRate());
	gtk_widget_show(label);
    return TRUE;
}

char *MEM_UseRate() {
	FILE *fp;
	char buffer[64];
	char name[32];
	float MemFree = 0,MemTotal = 0;
	float Mem_UseRate = 0;
	char *temp_mem = (char *)malloc(sizeof(char) * 100);
	if((fp = fopen("/proc/meminfo","r")) == NULL) {
		perror("fopen /proc/meminfo");
		exit(1);
	}

	fgets(buffer,sizeof(buffer),fp);
    sscanf(buffer,"%s %f %s",name,&MemTotal,name);  
    memset(buffer,0x00,sizeof(buffer));  
    fgets(buffer,sizeof(buffer),fp);  
    sscanf(buffer,"%s %f %s",name,&MemFree,name);  
	
	Mem_UseRate = (MemTotal-MemFree) / MemTotal;
	sprintf(temp_mem,"MemTotal:\t%0.0fKB\nMemFree:\t\t%0.0fKB\n内存使用率:\t%0.5f%%",MemTotal,MemFree,Mem_UseRate);

	fclose(fp);
	return temp_mem;
}
