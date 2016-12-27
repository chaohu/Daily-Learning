#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

struct passwd *getpwuid();
struct group *getgrgid();
int pridetail(struct stat statbuf);
void printdir(char *dir,int depth);

int main() {
    printdir(".",0);
    return 0;
}

void printdir(char *dir,int depth) {
    int i = 0;
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
                for(i = 0;i < depth;i = i + 4) printf("    ");
                printf("d");
                pridetail(statbuf);
                printf(" folder:%d %s\n",depth,entry->d_name);
                printdir(entry->d_name,depth+4);
            }
        }
        else {
            for(i = 0;i < depth;i = i + 4) printf("    ");
            printf("-");
            pridetail(statbuf);
            printf(" file:%d %s\n",depth,entry->d_name);
        }
    }
    chdir("..");
    closedir(dp);
}

//权限信息输出
int pridetail(struct stat statbuf) {
    struct passwd *pw_ptr;
    struct group *grp_ptr;
    struct tm *lmodifytime;

    //文件所有者权限
    if(statbuf.st_mode&S_IRUSR) printf("r");
    else printf("-");
    if(statbuf.st_mode&S_IWUSR) printf("w");
    else printf("-");
    if(statbuf.st_mode&S_IXUSR) printf("x");
    else printf("-");

    //用户组权限
    if(statbuf.st_mode&S_IRGRP) printf("r");
    else printf("-");
    if(statbuf.st_mode&S_IWGRP) printf("w");
    else printf("-");
    if(statbuf.st_mode&S_IXGRP) printf("x");
    else printf("-");
    
    //其他用户权限
    if(statbuf.st_mode&S_IROTH) printf("r");
    else printf("-");
    if(statbuf.st_mode&S_IWOTH) printf("w");
    else printf("-");
    if(statbuf.st_mode&S_IXOTH) printf("x");
    else printf("-");

    //inode节点号,硬链接个数
    printf(" %lu",statbuf.st_nlink);

    //用户名
    pw_ptr = getpwuid(statbuf.st_uid);
    printf(" %s",pw_ptr->pw_name);

    //用户组名
    grp_ptr = getgrgid(statbuf.st_gid);
    printf(" %s",grp_ptr->gr_name);

    //文件大小
    printf(" %ld",statbuf.st_size);

    //上次更新时间
    lmodifytime = localtime(&(statbuf.st_mtime));
    printf(" %d月 %2d %02d:%02d",lmodifytime->tm_mon+1,lmodifytime->tm_mday,lmodifytime->tm_hour,lmodifytime->tm_min);

    return 0;
}
