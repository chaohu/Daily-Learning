#include "task4.h"
#include <sys/utsname.h>

gint SYS_Refresh(gpointer label) {
	struct utsname u_name;
	char sysinfo[1000];
	if ((uname(&u_name)) < 0) {   
		printf("uname()failed\n");
		exit(1);
	}
	strcpy(sysinfo, "系统:						");
	strcat(sysinfo, u_name.sysname);
	strcat(sysinfo, "\n用户名:					");
	strcat(sysinfo, u_name.nodename);
	strcat(sysinfo, "\n系统版本:					");
	strcat(sysinfo, u_name.release);
	strcat(sysinfo, "\n架构:						");
	strcat(sysinfo, u_name.machine);

	gtk_label_set_text(label,sysinfo);
	gtk_widget_show(label);
	return TRUE;
}

gint show_time(gpointer label) {
	times = time(NULL);
	lmodifytime = localtime(&(times));
	sprintf(buf_time,"当前时间：				%0d月%2d日%02d:%02d:%02d",lmodifytime->tm_mon+1,lmodifytime->tm_mday,lmodifytime->tm_hour,lmodifytime->tm_min,lmodifytime->tm_sec);
	gtk_label_set_text(label,buf_time);
	return 1;
}
