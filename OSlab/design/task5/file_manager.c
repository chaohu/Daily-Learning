#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>  
#include<string.h>  
#include"user.h"  
#include"dirent.h"  
#include"block.h"  
#include"inode.h"  
   
int main(int argc, char * *argv) {  
       if (0) {  
              initUser();  
              initBlock();  
              initRootD();  
              initInode();  
       }  
   
       struct user allUsers[TOTAL_USER];  
       struct inode allInodes[TOTAL_INODE];  
       struct dirent allDirents[TOTAL_DIRENT];  
       unsigned short allBlocks[TOTAL_BLOCK];  
   
       struct user * nowUser;  
   
       int choise;  
   
       bool controler = true;  
   
       char name[USER_NAME_MAX_LENGTH];  
       char password[USER_PASSWORD_MAX_LENGTH];  
       char dirent_name[DIRENT_NAME_LENGTH_MAX];  
       char file_name[DIRENT_NAME_LENGTH_MAX];  
       char file_content[INODE_TO_BLOCK * FILE_BLOCK_MAX_LENGTH];  
   
       printf("---欢迎使用Lee制作的模拟文件系统---\n"  
                     "本文件系统又命名为YY文件系统\n");  
   
       //登录和注册的循环  
       while (controler) {  
   
              if (!openUser(allUsers)) {  
                     exit(1);  
              }  
   
              printf("请选择\n1: 老用户登录\t 2: 新用户注册\t 3：退出\n");  
              scanf("%d", &choise);  
              printf("你的输入是：%d\n", choise);  
   
              switch (choise) {  
              case 1:  
                     printf("欢迎你，老用户\n");  
                     printf("请输入用户名：\n");  
                     scanf("%s", name);  
                     printf("请输入密码:\n");  
                     scanf("%s", password);  
                     nowUser = login(allUsers, name, password);  
                     if (nowUser == NULL) {  
                            printf("你输入的用户名或密码有错误\n");  
                            continue;  
                     } else {  
                            if (!openRoot(allDirents)) {  
                                   printf("读取根目录的时候出错，请重新登录\n");  
                                   continue;  
                            }  
                            printf("你已经成功登录到Lee到文件系统\n");  
                            //进入文件系统后的循环  
                            while (allDirents != NULL && openInode(allInodes)  
                                          && openBlock(allBlocks)) {  
                                   printf("%s@Lee:/\n", nowUser->user_name);  
                                   listDirent(allDirents, allInodes);  
                                   if (allDirents[0].inode_num == allDirents[1].inode_num) {  
                                          printf("请选择\n"  
                                                        "1: 创建一个目录\t 2: 进入一个目录\t 3：删除一个目录\n"  
                                                        "4：创建一个文件\t 5：打开一个文件\t 6：删除一个文件\n"  
                                                        "7：退出\n");  
                                   } else {  
                                          printf("请选择\n"  
                                                        "1：创建一个目录\t 2：进入一个目录\t 3：删除一个目录\n"  
                                                        "4：创建一个文件\t 5：打开一个文件\t 6：删除一个文件\n"  
                                                        "7：返回上一级目录\n");  
                                   }  
                                   int action;  
                                   scanf("%d", &action);  
   
                                   unsigned short inode_num; //获取分配到到inode的序号  
                                   unsigned short protection; //设置保护位  
                                   unsigned short inode_i; //inode到序号  
                                   int dir_i; //目录项序号  
                                   unsigned short block_d[INODE_TO_BLOCK]; //删除的block的块序列  
   
                                   switch (action) {  
                                   case 1:  
                                          printf("请输入目录名：\n");  
                                          scanf("%s", dirent_name);  
                                          if (checkDir(allDirents, dirent_name) != DIRENT_UNDEFIEN) {  
                                                 printf("你输入到目录名重复，请重新输入!!\n");  
                                                 continue;  
                                          }  
                                          inode_num = createDirentI(allInodes, allBlocks,  
                                                        nowUser);  
                                          if (inode_num != INODE_UNUSERD) {  
                                                 if (!createDirentD(allDirents, dirent_name,  
                                                               inode_num)) {  
                                                        printf("创建目录项dirent到时候发生ERROR");  
                                                        exit(1);  
                                                 } else {  
                                                        createChildD(allDirents[0].inode_num, inode_num,  
                                                                      allInodes[inode_num].disk_add);  
                                                        saveBlock(allBlocks);  
                                                        saveInode(allInodes);  
                                                        saveDir(allDirents, allInodes);  
                                                        printf("成功创建了一个目录\n");  
                                                 }  
                                          } else {  
                                                 printf("分配INODE的时候发生ERROR");  
                                                 exit(1);  
                                          }  
                                          break;  
                                   case 2:  
                                          printf("请输入目录名：\n");  
                                          scanf("%s", dirent_name);  
                                          dir_i = checkDir(allDirents, dirent_name);  
                                          if (dir_i == DIRENT_UNDEFIEN) {  
                                                 printf("你输入到目录名有误，请重新输入!!\n");  
                                                 continue;  
                                          }  
                                          if (!openDir(allDirents, allInodes, dir_i)) {  
                                                 printf("打开目录的时候出错，请重新尝试!!\n");  
                                                 continue;  
                                          }  
                                          break;  
                                   case 3:  
                                          printf("请输入要删除的目录名：\n");  
                                          scanf("%s", dirent_name);  
                                          dir_i = checkDir(allDirents, dirent_name);  
                                          if (dir_i == DIRENT_UNDEFIEN) {  
                                                 printf("你输入到目录名有误，请重新输入!!\n");  
                                                 continue;  
                                          }  
                                          if (!isDirentEmpty(allDirents, allInodes, dir_i)) {  
                                                 printf("该目录下面有子文件或者子目录，请谨慎删除!!\n");  
                                                 continue;  
                                          } else {  
                                                 inode_i = deleteDir(allDirents, dir_i);  
                                                 if (inode_i != INODE_UNUSERD) {  
                                                        if (deleteInode(allInodes, block_d, inode_i)) {  
                                                               if (deleteBlock(block_d)) {  
                                                                     if (retrieveBlocks(block_d,  
                                                                                    allBlocks)) {  
                                                                             saveBlock(allBlocks);  
                                                                             saveInode(allInodes);  
                                                                             saveDir(allDirents, allInodes);  
                                                                            printf("成功删除了该文件!!\n");  
                                                                      }else {  
                                                                            printf("重置该文件的磁盘块配置文件出错!!\n");  
                                                                      }  
                                                               } else {  
                                                                     printf("删除该文件的block出错!!\n");  
                                                               }  
                                                        }  
                                                 } else {  
                                                        printf("删除该文件的dirent出错!!\n");  
                                                 }  
                                          }  
                                          break;  
                                   case 4:  
                                          printf("请输入文件名：\n");  
                                          scanf("%s", file_name);  
                                          if (checkDir(allDirents, file_name) != DIRENT_UNDEFIEN) {  
                                                 printf("你输入到目录名重复，请重新输入!!\n");  
                                                 continue;  
                                          }  
                                          printf("请输入文件的内容：\n");  
                                          scanf("%s", file_content);  
                                          printf("请设置文件保护信息\n 1：只读\t2：只写\t3：读和写\n");  
                                          protection = 0; //设置保护位  
                                          scanf("%hu", &protection);  
//                                        printf("%hu\n", protection);  
                                          inode_num = createFileI(allInodes, allBlocks, nowUser,  
                                                        strlen(file_content), protection);  
                                          printf("%d\n", inode_num);  
                                          if (inode_num != INODE_UNUSERD) {  
                                                 if (!creatFileD(allDirents, file_name, inode_num)) {  
                                                        printf("创建目录项dirent到时候发生ERROR");  
                                                        exit(1);  
                                                 } else {  
                                                        createChildF(allInodes[inode_num].disk_add,  
                                                                      file_content);  
                                                        saveBlock(allBlocks);  
                                                        saveInode(allInodes);  
                                                        saveDir(allDirents, allInodes);  
                                                        printf("成功创建了一个文件\n");  
                                                 }  
                                          } else {  
                                                 printf("分配INODE的时候发生ERROR");  
                                                 exit(1);  
                                          }  
                                          break;  
                                   case 5:  
                                          printf("请输入要读取的文件名：\n");  
                                          scanf("%s", file_name);  
                                          dir_i = checkDir(allDirents, file_name);  
                                          if (dir_i == DIRENT_UNDEFIEN) {  
                                                 printf("你输入的文件名有误，请重新操作!!\n");  
                                                 continue;  
                                          }  
                                          readFile(allDirents, allInodes, dir_i);  
                                          printf("是否对文件进行读写保护位设置\n"  
                                                        "请选择\n1: 是\t 2: 否并且退出\n");  
                                          int operation;  
                                          scanf("%d", &operation);  
                                          if (operation == 1) {  
                                                 printf("请设置文件保护信息\n 1：只写\t2：只读\t3：读和写\n");  
                                                 protection = 0; //设置保护位  
                                                 scanf("%hu", &protection);  
                                                 if(setProtection(&allInodes[allDirents[dir_i].inode_num],protection)){  
                                                        saveInode(allInodes);  
                                                        printf("请设置文件保护信息成功\n");  
                                                 }else{  
                                                        printf("请设置文件保护信息失败\n");  
                                                 }  
                                          }  
                                          break;  
                                   case 6:  
                                          printf("请输入要删除的文件名：\n");  
                                          scanf("%s", file_name);  
                                          dir_i = checkDir(allDirents, file_name);  
                                          if (dir_i == DIRENT_UNDEFIEN) {  
                                                 printf("你输入的文件名有误，请重新操作!!\n");  
                                                 continue;  
                                          }  
                                          inode_i = deleteDir(allDirents, dir_i);  
                                          if (inode_i != INODE_UNUSERD) {  
                                                 if (deleteInode(allInodes, block_d, inode_i)) {  
                                                        if (deleteBlock(block_d)) {  
                                                               if (retrieveBlocks(block_d, allBlocks)) {  
                                                                      saveBlock(allBlocks);  
                                                                      saveInode(allInodes);  
                                                                      saveDir(allDirents, allInodes);  
                                                                     printf("成功删除了该文件!!\n");  
                                                               } else {  
                                                                     printf("重置该文件的磁盘块配置文件出错!!\n");  
                                                               }  
                                                        } else {  
                                                               printf("删除该文件的block出错!!\n");  
                                                        }  
                                                 }  
                                          } else {  
                                                 printf("删除该文件的dirent出错!!\n");  
                                          }  
                                          break;  
                                   case 7:  
                                          if (allDirents[0].inode_num  
                                                        == allDirents[1].inode_num) {  
                                                 //Do nothing  
                                                 printf("---欢迎你再次使用YY文件系统！---\n");  
                                                 exit(1);  
                                          } else {  
                                                 dir_i = checkDir(allDirents, ".."); //其实就是重复第二部，打开“..”文件夹  
                                                 if (dir_i == DIRENT_UNDEFIEN) {  
                                                        printf("你输入到目录名有误，请重新输入!!\n");  
                                                        continue;  
                                                 }  
                                                 if (!openDir(allDirents, allInodes, dir_i)) {  
                                                        printf("打开目录的时候出错，请重新尝试!!\n");  
                                                        continue;  
                                                 }  
                                          }  
                                          break;  
                                   default:  
                                          printf("你的选择有错误，请重新选择！\n");  
                                          break;  
                                   }  
                            }  
                            printf("读取系统目录出错，请重新登录尝试\n");  
                            continue;  
                     }  
                     break;  
              case 2:  
                     printf("欢迎你，老用户\n");  
                     printf("请输入用户名：\n");  
                     scanf("%s", name);  
                     while (checkUser(allUsers, name) != USER_UNDEFINE) {  
                            printf("你输入到用户名已被注册，请重新输入\n");  
                            scanf("%s", name);  
                     }  
                     printf("请输入密码:\n");  
                     scanf("%s", password);  
                     if (!createUser(allUsers, name, password)) {  
                            printf("注册的过程发生错误，请重新选择\n");  
                     } else {  
                            saveUser(allUsers);  
                            printf("注册成功，请进行登录或其他操作！\n");  
                     }  
                     break;  
              case 3:  
                     controler = false;  
                     printf("已经为你退出系统！\n");  
                     break;  
              default:  
                     printf("你的选择有错误，请重新选择！\n");  
                     break;  
              }  
       }  
   
}  