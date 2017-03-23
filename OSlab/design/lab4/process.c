#include "task4.h"

/*
 * 说明：获取进程信息
 */
gint get_proc(gpointer clist) {
    DIR *dir;
    struct dirent *ptr;
    if(!(dir = opendir("/proc"))) return 0;
	
	gtk_clist_clear(GTK_CLIST(clist));
    //读取目录
    while((ptr =  readdir(dir))) {//循环读出所有的进程文件
        if(ptr->d_name[0] > '0' && ptr->d_name[0] <= '9') {
            //获取进程信息
            proc_info_st info;
            read_proc(&info,ptr->d_name,clist);//读取信息
        }
    }
	closedir(dir);
	return 1;
}

/*
 * 说明：根据进程pid获取进程信息存放在proc_info_st结构体中
 */
void read_proc(proc_info_st *info,const char *c_pid,gpointer clist) {
    FILE *fp = NULL;
    char file[512] = {0};
    char line_buff[1024] = {0}; //读取行的缓冲区

    sprintf(file,"/proc/%s/status",c_pid);  //读取status文件
    if(!(fp = fopen(file,"r"))) {
        perror("read file fail");
        return;
    }

    char name[256];
    //先读取进程名称
    read_line(fp,line_buff,1024,PROC_NAME_LINE);
	sscanf(line_buff,"%s %s",name,(info->name));

    fseek(fp,0,SEEK_SET);   //回到文件头部
    read_line(fp,line_buff,1024,PROC_PID_LINE);
	sscanf(line_buff,"%s %s",name,info->pid);

    fseek(fp,0,SEEK_SET);   //回到文件头部
    read_line(fp,line_buff,1024,PROC_STATE_LINE);
	sscanf(line_buff,"%s %s",name,info->state);

    fseek(fp,0,SEEK_SET);   //回到文件头部
    read_line(fp,line_buff,1024,PROC_VMSIZE_LINE);
	sscanf(line_buff,"%s %s",name,info->vmsize);
	if(strcmp(name,"VmSize:")) {
		info->vmsize[0] = '0';
		info->vmsize[1] = '\0';
	}

    fclose(fp);

    sprintf(file,"/proc/%s/stat",c_pid);  //读取stat文件
	if(!(fp = fopen(file,"r"))) {
        perror("read file fail");
        return;
    }
    read_line(fp,line_buff,1024,1);
	sscanf(line_buff, "%*s %*s %*s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s", info->ppid, info->priority);
	fclose(fp);

	gchar *list[1][6] = {
		{info->name, info->pid, info->ppid, info->state, info->vmsize, info->priority}
	};

	gtk_clist_append((GtkCList*) clist, list[0]);
	gtk_clist_thaw((GtkCList *) clist);
}

/*
 * 说明：读取文件的一行到buff
 */
int read_line(FILE *fp,char *buff,int buff_len,int line) {
    if(!fp) return FALSE;
    char line_buff[buff_len];
    int i;
    //读取指定行的前l-1行,转到指定行
    for(i = 0;i < line-1;i++) {
        if(!fgets(line_buff,sizeof(line_buff),fp)) {
            return FALSE;
        }
    }

    //读取指定行
    if(!fgets(line_buff,sizeof(line_buff),fp)) {
        return FALSE;
    }
    memcpy(buff,line_buff,buff_len);
    return TRUE;
}
