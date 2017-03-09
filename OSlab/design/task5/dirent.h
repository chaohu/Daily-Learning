#define UNDEFIEN 0  
   
#define DIRENT_TYPE 1  
#define FILE_TYPE 2  
   
#define DIRENT_NAME_LENGTH_MAX 128  
#define TOTAL_DIRENT 64  
#define DIRENT_UNDEFIEN 64  
   
struct dirent  
{  
       unsigned short inode_num;  
       unsigned short dirent_type;  
       char dirent_name[DIRENT_NAME_LENGTH_MAX];  
};  
   
void initRootD();  
   
void saveRoot(struct dirent * d);  
   
bool createDirentD(struct dirent * allDirents,const char * name,unsigned short inode_num);  
   
bool creatFileD(struct dirent * allDirents,const char * name,unsigned short inode_num);  
   
bool isDirentEmpty(struct dirent * allDirents,struct inode * node,int index);  
   
unsigned short deleteDir(struct dirent * allDirents,int index);  

void listDirent(struct dirent * allDirents,struct inode * allInodes);  
   
bool openRoot(struct dirent * d);  
   
struct dirent * openDir(struct dirent * allDirents,int index,struct inode * node);  
   
void saveDir(struct dirent * allDirents,struct inode * allInodes);  
   
bool closeDir(struct dirent * allDirents,int index,struct inode * node);  
   
void createChildD(unsigned short father_inode_num,unsigned short child_inode_num,unsigned short * disk_add);  
   
void createChildF(unsigned short * disk_add,char * file_content);  
   
void readFile(struct dirent * allDirents,struct inode * node,int index);  
   
int checkDir(struct dirent * allDirents,const char * name);  
   
bool openDir(struct dirent * allDirents,struct inode * node,int index); 