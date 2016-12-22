#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

int permission(unsigned short st_mode);
void printdir(char *dir,int depth);


int main() {
    printdir(".",0);
    return 0;
}

void printdir(char *dir,int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL) {
        printf("打开当前目录失败\n");
        exit(1);
    }
    chdir(dir);
    while((entry = readdir(dp))) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(entry->d_name,".") && strcmp(entry->d_name,"..")) {
                printf("d");
                permission(statbuf.st_mode);
                printf(" %u ",statbuf.st_ino);
                printf("目录：%d\t%s\n",depth,entry->d_name);
                printdir(entry->d_name,depth+4);
            }
        }
        else {
            printf("文件：%d\t%s\n",depth,entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

//权限信息输出
int permission(unsigned short st_mode) {

    //文件所有者权限
    if(st_mode&S_IRUSR) printf("r");
    else printf("-");
    if(st_mode&S_IWUSR) printf("w");
    else printf("-");
    if(st_mode&S_IXUSR) printf("x");
    else printf("-");

    //用户组权限
    if(st_mode&S_IRGRP) printf("r");
    else printf("-");
    if(st_mode&S_IWGRP) printf("w");
    else printf("-");
    if(st_mode&S_IXGRP) printf("x");
    else printf("-");
    
    //其他用户权限
    if(st_mode&S_IROTH) printf("r");
    else printf("-");
    if(st_mode&S_IWOTH) printf("w");
    else printf("-");
    if(st_mode&S_IXOTH) printf("x");
    else printf("-");

    return 0;
}
