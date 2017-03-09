#define TOTAL_BLOCK 4096  
#define BLOCK_UNUSED 4096  
   
#define UNDEFIEN 0  
   
#define DIRENT_TYPE 1  
#define FILE_TYPE 2  
   
void initBlock();  
   
bool openBlock(unsigned short * block);  
   
void saveBlock(unsigned short * block);  
   
bool applyBlocks(unsigned short * b,unsigned short * block,int num);  
   
bool retrieveBlocks(unsigned short * b,unsigned short * block);  
   
bool deleteBlock(unsigned short * b); 