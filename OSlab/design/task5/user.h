#define TOTAL_USER 32     //该文件系统允许到最大用户数目  
#define USER_UNDEFINE 32  
   
#define USER_NAME_MAX_LENGTH 32  //用户名到最大长度  
#define USER_PASSWORD_MAX_LENGTH 16   //密码到最大长度  
   
#define SUPERUSER 0  
   
struct user        
{  
       unsigned int user_id;  
       char user_name[USER_NAME_MAX_LENGTH];  
       char user_password[USER_PASSWORD_MAX_LENGTH];  
};  
   
int checkUser(struct user * allUsers,const char * name);  
   
struct user * login(struct user * allUsers,const char * name,const char * password);  
   
bool createUser(struct user * allUsers,const char * name,const char * password);  
   
bool deleteUser(struct user * allUsers,struct user * u);  
   
void initUser();  
   
bool openUser(struct user * u);  
   
void listUser(struct user * u);  
   
void saveUser(struct user * u); 