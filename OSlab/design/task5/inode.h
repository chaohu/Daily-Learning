#include<time.h>
#define TOTAL_INODE 1024  
#define INODE_TO_BLOCK 4   //每个inode可以映射到4个磁盘块  
#define FILE_BLOCK_MAX_LENGTH 8  //每个磁盘块存放的文件类型大小为8字节  
   
#define INODE_UNUSERD 1024  
   
#define WRITE_ONLY 1  
#define READ_ONLY 2
#define WRITE_AND_READ 3  
   
struct inode  
{  
       unsigned short file_type;  //文件类型 目录 或者 文件  
       unsigned short protection; //保护位 读 写 读写同时  
       unsigned int link_num;    //指向该节点到目录项  
       unsigned int user_id;   //文件所属用户到id  
       unsigned long file_size;    //文件的大小  
       unsigned short disk_add[INODE_TO_BLOCK];     //12个磁盘块到地址,每块地址存储的数据到大小是8bytes,支持32bytes的普通文件，还有特定的目录项文件  
       time_t access_time;   //文件被最后访问到时间  
       time_t modification_time;   //文件最后被修改到时间  
       time_t create_time;   //修改原来到结构，改为i节点被确定使用到时间  
};  
   
void initInode();  
   
bool openInode(struct inode * node);  
   
void saveInode(struct inode * node);  
   
void listInode(struct inode * node);  
   
unsigned short createDirentI(struct inode * node,unsigned short * block,struct user * u);  
   
unsigned short  createFileI(struct inode * node,unsigned short * block,struct user * u,unsigned long size,unsigned short protection);  
   
bool deleteInode(struct inode * node,unsigned short * block,unsigned short index);  
   
bool setProtection(struct inode * i,unsigned short p);  
   
bool setCreateTime(struct inode * i,time_t time);  
   
bool setAccessTime(struct inode * i,time_t time);  
   
bool setModificationTime(struct inode * i,time_t time);