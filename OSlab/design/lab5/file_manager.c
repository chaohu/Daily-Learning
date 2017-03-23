#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HELP 0
#define LS 1
#define CD 2
#define MKDIR 3
#define TOUCH 4
#define RMF 5
#define RMD 6
#define WRITE 7
#define READ 8
#define EXIT 9

#define DISK "disk.dat"			//磁盘块号文件
#define DNodeNum 128 			//目录节点数目
#define FNodeNum 1024			//文件节点数目
#define BlkNum (80 * 1024)		//磁盘块的数目
#define BlkSize 1024			//磁盘块大小为1K
#define BlkPerFile 80			//每个文件包含的最大的磁盘块数目
#define SuperBeg sizeof(int)	//超级块的起始地址
#define DNodeBeg sizeof(SuperBlk)//目录节点的起始地址
#define FNodeBeg DNodeBeg+DNodeNum*sizeof(Dir_Node)//文件节点的起始地址
#define BlockBeg FNodeBeg+FNodeNum*sizeof(File_Node)//数据区的起始地址

typedef struct SuperBlk{
	int dnode_map[DNodeNum];	//目录节点位图
	int fnode_map[FNodeNum];	//文件节点位图
    int blk_map[BlkNum];		//磁盘块位图
}SuperBlk;

typedef struct Dir_Node {		//目录节点
	int dir_num;				//目录节点编号
	char dir_name[32];  		//目录名
	int child_dir[8];			//子目录索引
	int dir_count;				//当前子目录数
	int child_file[16];			//子文件索引
	int file_count;				//当前子文件数
	int parent;					//父目录索引
}Dir_Node;

typedef struct File_node {
	int file_num;				//文件节点编号
	char file_name[32];			//文件名
	int block[BlkPerFile];		//文件占用的磁盘块编号
	int blk_count;				//文件占用磁盘块数
	int size_rest;				//文件一个磁盘块不满时占用的字节数
	int parent;					//父目录索引
}File_Node;

FILE *Disk;
SuperBlk super_blk;				//文件系统的超级块
Dir_Node curr_dir;				//当前目录节点指针
Dir_Node buff_dir_node[8];		//当前目录下的目录结点
File_Node buff_file_node[16];	//当前目录下的文件结点
int dnode_num = 0;
char path[40] = "root";
char cmd[5][20];				//命令行输入
//系统支持的命令
char SYS_CMD[10][20] = {"help","ls","cd","mkdir","touch","rmf","rmd","write","read","exit"};

int init_fs();
int analyse(char *str);
int check_name(char *name);
int apply_d_node();
int apply_f_node();
int create_dir(char *name);
int create_file(char *name);
int del_subdir(int num);
int del_subfile(int num);
int del_dir(char *name);
int del_file(char *name);
int save_dir(int dnode_num);
int open_dir(int dnode_num);
int change_dir(char *name);
int show_dir_file();
int help();
int write_file(char *name);
int read_file(char *name);


//运行文件系统，处理用户命令
int main() {
	int i = 0;
    char input[128];
	Disk = fopen(DISK,"r+");			//打开模拟文件块文件
	if(!Disk) {
		printf("模拟磁盘文件打开失败！");
		return 0;
	}
	init_fs();
    do {
		printf("%s > ", curr_dir.dir_name);
        fgets(input, 128, stdin);
        switch(analyse(input))
        {
            case HELP:
                help();break;
            case LS:
                show_dir_file();break;
            case CD:
                change_dir(cmd[1]);break;
            case MKDIR:
                create_dir(cmd[1]);break;
            case TOUCH:
                create_file(cmd[1]);break;
            case RMF:
                del_file(cmd[1]);break;
            case RMD:
                del_dir(cmd[1]);break;
			case WRITE:
				write_file(cmd[1]);break;
			case READ:
				read_file(cmd[1]);break;
            case EXIT: {
				fseek(Disk,SuperBeg,SEEK_SET);
				fwrite(&super_blk,sizeof(SuperBlk),1,Disk);
				save_dir(curr_dir.dir_num);
                return 0;
                break;
			}
            default:
                printf("不支持的命令\n");
                break;
        }
    } while(1);
}


int init_fs(void)  
{
	int init_flag = 0;
    fseek(Disk,0,SEEK_SET);					//文件系统起始位置 
	fread(&init_flag,sizeof(int),1,Disk);	//判断是否是第一次启动系统
	if(init_flag != 1) {
		init_flag = 1;
		fseek(Disk,0,SEEK_SET);
		fwrite(&init_flag,sizeof(int),1,Disk);
		memset(super_blk.dnode_map,0,sizeof(super_blk.dnode_map));
		memset(super_blk.fnode_map,0,sizeof(super_blk.fnode_map));
		memset(super_blk.blk_map,0,sizeof(super_blk.blk_map));
		super_blk.dnode_map[0] = 1;
		curr_dir.dir_num = 0;
		strcpy(curr_dir.dir_name,"root");
		curr_dir.dir_count = 0;
		curr_dir.file_count = 0;
		curr_dir.file_count = 0;
	}
	else {
		fseek(Disk,SuperBeg,SEEK_SET);			//超级块起始位置 
		fread(&super_blk,sizeof(SuperBlk),1,Disk);//读取超级块  
		open_dir(0);
	}
    return 1;
}



//分析命令
int analyse(char* str)
{
    int i;
    for(i = 0; i < 5; i++) cmd[i][0] = '\0';
    sscanf(str, "%s %s %s %s %s",cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);

    for(i = 1; i < 10; i++)
    {
        if(strcmp(cmd[0], SYS_CMD[i]) == 0) return i;
    }
    return 0;
}


//检查目录或文件名是否与已有名称重复
int check_name(char *name) {
	int i = 0;
	for(i = 0;i < curr_dir.dir_count;i++) {
		if(strcmp(buff_dir_node[i].dir_name,name) == 0) return 0;
	}
	for(i = 0;i < curr_dir.file_count;i++) {
		if(strcmp(buff_file_node[i].file_name,name) == 0) return 0;
	}
	return 1;
}

//申请新的目录节点
int apply_d_node() {
	int i = 0;
	for(i = 0;i < DNodeNum;i++) {
		if(!super_blk.dnode_map[i]) return i;
	}
	return -1;
}

//申请新的文件节点
int apply_f_node() {
	int i = 0;
	for(i = 0;i < FNodeNum;i++) {
		if(!super_blk.fnode_map[i]) return i;
	}
	return -1;
}

//申请新的磁盘块
int apply_blk() {
	int i = 0;
	for(i = 0;i < BlkNum;i++) {
		if(!super_blk.blk_map[i]) return i;
	}
	return -1;
}

//创建目录
int create_dir(char *name) {				//在当前的目录下创建目录
	int i = 0;
	if(name[0] == '\0') {
		printf("目录名为空，创建失败!\n");
		return 0;
	}
	if(curr_dir.dir_count == 8) {			//如果父目录已满，则创建失败
		printf("当前目录下目录已满,创建失败!\n");
		return 0;
	}
	if(check_name(name) == 0) {
		printf("目录名冲突，创建失败!\n");
		return 0;
	}
	i = apply_d_node();
	if(i == -1) {
		printf("目录节点已满，申请目录节点失败!\n");
		return 0;
	}
	super_blk.dnode_map[i] = 1;

	//新建新目录节点
	buff_dir_node[curr_dir.dir_count].dir_num = i;
	strcpy(buff_dir_node[curr_dir.dir_count].dir_name,name);
	buff_dir_node[curr_dir.dir_count].dir_count = 0;
	buff_dir_node[curr_dir.dir_count].file_count = 0;
	buff_dir_node[curr_dir.dir_count].parent = curr_dir.dir_num;

	//修改当前目录节点
	curr_dir.child_dir[curr_dir.dir_count] = i;
	curr_dir.dir_count++;

	return 1;
}


//创建文件
int create_file(char *name) {				//在当前目录下创建文件
	int i = 0,j = 0;
	if(name[0] == '\0') {
		printf("文件名为空，创建失败!\n");
		return 0;
	}
	if(curr_dir.file_count >= 16) {		//如果父目录已满，则创建失败
		printf("当前目录下文件已满，创建失败!\n");
		return 0;
	}
	if(check_name(name) == 0) {
		printf("文件名冲突，创建失败!\n");
		return 0;
	}
	i = apply_f_node();
	if(i == -1) {
		printf("文件节点已满，申请文件节点失败!\n");
		return 0;	
	}
	j = apply_blk();
	if(j == -1) {
		printf("文件节点已满，申请文件节点失败!\n");
		return 0;
	}
	super_blk.fnode_map[i] = 1;
	super_blk.blk_map[j] = 1;

	buff_file_node[curr_dir.file_count].file_num = i;
	strcpy(buff_file_node[curr_dir.file_count].file_name,name);
	buff_file_node[curr_dir.file_count].block[0] = j;
	buff_file_node[curr_dir.file_count].blk_count = 1;
	buff_file_node[curr_dir.file_count].size_rest = 0;
	buff_file_node[curr_dir.file_count].parent = curr_dir.dir_num;

	curr_dir.child_file[curr_dir.file_count] = i;
	curr_dir.file_count++;

	return 1;
}

//删除目录
//递归删除目录的子目录
int del_subdir(int num) {
	int i = 0;
	Dir_Node temp_d;
	super_blk.dnode_map[num] = 0;
	fseek(Disk,DNodeBeg+sizeof(Dir_Node)*num,SEEK_SET);
	fread(&temp_d,sizeof(Dir_Node),1,Disk);
	for(i = 0;i < temp_d.dir_count;i++) del_subdir(temp_d.child_dir[i]);
	for(i = 0;i < temp_d.file_count;i++) del_subfile(temp_d.child_file[i]);
	return 1;
}

int del_subfile(int num) {
	int i = 0;
	File_Node temp_f;
	super_blk.fnode_map[num] = 0;
	fseek(Disk,FNodeBeg+sizeof(File_Node)*num,SEEK_SET);
	fread(&temp_f,sizeof(File_Node),1,Disk);
	for(i = 0;i < temp_f.blk_count;i++) super_blk.blk_map[temp_f.block[i]] = 0;
	return 1;
}

//删除当前目录下的某一个目录
int del_dir(char *name) {
	int i = 0,j = 0;
	if(name[0] == '\0') {
		printf("目录名为空，删除失败!\n");
		return 0;
	}
	for(i = 0;i < curr_dir.dir_count;i++) {
		if(strcmp(buff_dir_node[i].dir_name,name) == 0) {
			super_blk.dnode_map[buff_dir_node[i].dir_num] = 0;
			for(j = 0;j < buff_dir_node[i].dir_count;j++) del_subdir(buff_dir_node[i].child_dir[j]);
			for(j = 0;j < buff_dir_node[i].file_count;j++) del_subfile(buff_dir_node[i].child_file[j]);
			curr_dir.dir_count--;
			for(;i < curr_dir.dir_count;i++) {
				curr_dir.child_dir[i] = curr_dir.child_dir[i+1];
				buff_dir_node[i] = buff_dir_node[i+1];
			}
			return 1;
		}
	}
	printf("无此目录，删除失败！\n");
	return 0;
}


//删除文件
int del_file(char *name) {           //删除当前目录下的文件
	int i = 0,j = 0;
	if(name[0] == '\0') {
		printf("文件名为空，删除失败!\n");
		return 0;
	}
	for(i = 0;i < curr_dir.file_count;i++) {
		if(strcmp(buff_file_node[i].file_name,name) == 0) {
			super_blk.fnode_map[buff_file_node[i].file_num] = 0;
			for(j = 0;j < buff_file_node[i].blk_count;j++) super_blk.blk_map[buff_file_node[i].block[j]] = 0;
			curr_dir.file_count--;
			for(;i < curr_dir.file_count;i++) {
				curr_dir.child_file[i] = curr_dir.child_file[i+1];
				buff_file_node[i] = buff_file_node[i+1];
			}
			return 1;
		}
	}
	printf("无此文件，删除失败！\n");
	return 0;
}


//改变目录
int save_dir(int dnode_num)	{	//保存当前文件节点
    int	i = 0;
	//转到相应的位置
    fseek(Disk,DNodeBeg + sizeof(Dir_Node) * dnode_num,SEEK_SET);
    //写回相应的目录节点
    fwrite(&curr_dir,sizeof(Dir_Node),1,Disk);

	//写回当前目录下的目录节点进内存
    for(i = 0;i < curr_dir.dir_count;i++){  
        fseek(Disk,DNodeBeg+sizeof(Dir_Node)*(curr_dir.child_dir[i]),SEEK_SET);  
        fwrite(buff_dir_node + i,sizeof(Dir_Node),1,Disk);  
    }  
      
	//写回当前目录下的文件节点进内存
	for(i = 0;i < curr_dir.file_count;i++) {
        fseek(Disk,FNodeBeg+sizeof(File_Node)*(curr_dir.child_file[i]),SEEK_SET);  
	    fwrite(buff_file_node + i,sizeof(File_Node),1,Disk);  
	}

    return 1;
}


int open_dir(int dnode_num)  	//打开新的文件节点
{
    int	i = 0;
	//转到相应的位置
    fseek(Disk,DNodeBeg + sizeof(Dir_Node) * dnode_num,SEEK_SET);
    //读出相应的目录节点
    fread(&curr_dir,sizeof(Dir_Node),1,Disk);

	//读出当前目录下的目录节点进内存
    for(i = 0;i < curr_dir.dir_count;i++){  
        fseek(Disk,DNodeBeg+sizeof(Dir_Node)*(curr_dir.child_dir[i]),SEEK_SET);  
        fread(buff_dir_node + i,sizeof(Dir_Node),1,Disk);  
    }  
      
	//读出当前目录下的文件节点进内存
	for(i = 0;i < curr_dir.file_count;i++) {
        fseek(Disk,FNodeBeg+sizeof(File_Node)*(curr_dir.child_file[i]),SEEK_SET);  
	    fread(buff_file_node + i,sizeof(File_Node),1,Disk);  
	}

    return 1;
}


int change_dir(char *name) {	//改变工作目录
	int i = 0;
	int flag = 0;
	if(name[0] == '\0') {
		printf("目录名为空，改变失败!\n");
		return 0;
	}
	if(strcmp(name,".") == 0) flag = 1;
	else if(strcmp(name,"..") == 0) flag = 2;
	else {
		for(i = 0;i < curr_dir.dir_count;i++) {
			if(strcmp(buff_dir_node[i].dir_name,name) == 0) {
				flag = 3;
				break;
			}
		}
	}
	if(flag == 0) {
		printf("无此目录，进入失败！\n");
		return 0;
	}
	else if(flag == 1) return 1;
	else if(flag == 2) {
		if(curr_dir.dir_num == 0) {
			printf("当前为根目录!\n");
			return 2;
		}
		else {
			save_dir(curr_dir.dir_num);
			open_dir(curr_dir.parent);
			return 2;
		}
	}
	else if(flag == 3) {
		save_dir(curr_dir.dir_num);
		open_dir(curr_dir.child_dir[i]);
		return 3;
	}
}


//显示当前目录下的文件和子目录信息
int show_dir_file() {	
	int i = 0;
	for(i = 0;i < curr_dir.dir_count;i++) printf("[D]%s\t",buff_dir_node[i].dir_name);
	if(i) printf("\n");
	for(i = 0;i < curr_dir.file_count;i++) printf("[F]%s\t",buff_file_node[i].file_name);
	if(i) printf("\n");
	return 0;
}


//显示帮助信息
int help() {
    printf("command: \n\
    help    ---  show help menu \n\
    ls      ---  list the digest of the directory's children \n\
    cd      ---  change directory \n\
    mkdir   ---  make directory   \n\
    touch   ---  create a new file \n\
    rmf     ---  delete a file \n\
    rmd     ---  delete a directory \n\
    write   ---  write something to a file \n\
    read    ---  read a file \n\
    exit    ---  exit this system\n");
	return 1;
}

//写文件
int write_file(char *name) {
	int flag = 0;
	int i = 0;
	int blk_num = 0,size_rest = 0;
    char temp[1024];
	if(name[0] == '\0') {
		printf("文件名为空，写入失败!\n");
		return 0;
	}
	for(i = 0;i < curr_dir.file_count;i++) {
		if(strcmp(buff_file_node[i].file_name,name) == 0) {
			flag = 1;
			break;
		}
	}
	if(flag) {
		fgets(temp,1024,stdin);
		size_rest = strlen(temp)-1;
		if((size_rest + buff_file_node[i].size_rest) > 1024) {
			if(buff_file_node[i].blk_count >= 80) {
				printf("文件已经最大，写入失败!\n");
				return 0;
			}
			blk_num = apply_blk();
			if(blk_num == -1) {
				printf("磁盘块已满，写入失败！\n");
				return 0;
			}
			else {
				char temp_buff[1024];
				super_blk.blk_map[blk_num] = 1;
				buff_file_node[i].block[buff_file_node[i].blk_count] = blk_num;
				buff_file_node[i].blk_count++;
				fseek(Disk,BlockBeg+sizeof(char)*(buff_file_node[i].block[buff_file_node[i].blk_count-2])+buff_file_node[i].size_rest,SEEK_SET);
				fwrite(temp,sizeof(char)*(1024-buff_file_node[i].size_rest),1,Disk);
				fseek(Disk,BlockBeg+sizeof(char)*blk_num,SEEK_SET);
				fwrite(temp+1024-buff_file_node[i].size_rest,sizeof(char)*(size_rest-1024+buff_file_node[i].size_rest),1,Disk);
				buff_file_node[i].size_rest = size_rest-1024+buff_file_node[i].size_rest;
				return 1;
			}
		}
		else {
			fseek(Disk,BlockBeg+sizeof(char)*(buff_file_node[i].block[buff_file_node[i].blk_count-1])+buff_file_node[i].size_rest,SEEK_SET);
			fwrite(temp,sizeof(char)*size_rest,1,Disk);
			buff_file_node[i].size_rest += size_rest;
			return 1;
		}
	}
	else {
		printf("当前目录下无此文件，写入失败!\n");
		return 0;
	}
}

//读文件  
int read_file(char* name) {
	int flag = 0;
	int i = 0,j = 0;
	char temp[1024];

	if(name[0] == '\0') {
		printf("文件名为空，读出失败!\n");
		return 0;
	}
	for(i = 0;i < curr_dir.file_count;i++) {
		if(strcmp(buff_file_node[i].file_name,name) == 0) {
			flag = 1;
			break;
		}
	}

	if(flag) {
		for(j = 0;j < buff_file_node[i].blk_count-1;j++) {
			fseek(Disk,BlockBeg+sizeof(char)*buff_file_node[i].block[j],SEEK_SET);  
			fread(&temp,sizeof(temp),1,Disk);
			printf("%s",temp);
		}
		if(buff_file_node[i].size_rest) {
			fseek(Disk,BlockBeg+sizeof(char)*buff_file_node[i].block[buff_file_node[i].blk_count-1],SEEK_SET);  
			fread(&temp,sizeof(char)*(buff_file_node[i].size_rest),1,Disk);
			temp[buff_file_node[i].size_rest] = '\0';
			printf("%s",temp);
			printf("\n");
		}
    	return 1;  
	}
	else {
		printf("当前目录下无此文件，读出失败!\n");
		return 0;
	}
}
