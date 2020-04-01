#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

// a function to find length of string
uint
strlength(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

// function to coopy one string to another
void
stringcpy(char *src, char *dest)
{
  int i = 0;
  int len = strlength(src);
  while(i < len )
  {
    *(dest+i) = src[i];
    i++;
  }
  *(dest+i) = '\0';
  *(src+i) = '\0';
} 

//this function finds the name of the current directory and updates the name variable with it.
int
get_dname(char *curr, char* paren, char *name)
{
  int fd;
  struct dirent de;
  struct stat st;

//open the current directory and find it's inode number
  if((fd = open(curr, 0)) < 0){
    printf(2, "pwd: cannot open %s\n", curr);
    return -1;
  }
  if(fstat(fd, &st) < 0){
    printf(2, "pwd: cannot stat %s\n", curr);
    close(fd);
    return -1;
  }
//close current directory
  uint curr_ino = st.ino;   //current directory inode number.
   close(fd);

//now open the parent directory and read it as struct dirent
//if the inode number matches, then that's the current directory we are looking for
//if the inode of current directory and parent directory are same, it is the root node

if((fd = open(paren, 0)) < 0){
    printf(2, "pwd: cannot open %s\n", paren);
    return -1;
  }
  if(fstat(fd, &st) < 0){
    printf(2, "pwd: cannot stat %s\n", paren);
    close(fd);
    return -1;
  }

 uint p_ino = st.ino;

 if(p_ino == curr_ino)    //root directory
 {
     name[0] = '/';
     name[1] = '\0';
     return 1;      //return 1 when the directory is root
 }
  
 while(read(fd, &de, sizeof(de)) == sizeof(de))
 {
     if(de.inum == curr_ino)
     {
         //name = de.name;
         stringcpy(de.name, name);
         return 0;
        break;
     }
 } 
return -1;
  close(fd);
}

//this functions adds "/.." to the parent directory to go one folder up
void
concatenate(char *string)
{
  int i = 0;
  while(i < strlength(string))
    i++;
  string[i] = '/';
  string[i+1] = '.';
  string[i+2] = '.';
  string[i+3] = '\0';
}

int
main()
{
    char cur_dir[50];
    *cur_dir = '.';
    char paren_dir[50];
    *paren_dir = '.';
    *(paren_dir + 1) = '.';
    char path[50];
    path[0] = '\0';
    char name[50];
    char temp[50];
    int flag = 0;
    
    while(get_dname(cur_dir, paren_dir, name) == 0)
    {
      stringcpy(paren_dir, cur_dir);
      concatenate(paren_dir);

    if(path[0] == '\0' && flag == 0)
        stringcpy(name,path);
    else
      {
        flag = 1;
        stringcpy(path, temp);
        //move already existing path string and add the current name to the begining of the path.
        int j;
        for( j = 0; j<strlength(name)+1; j++)
        {;}
        for(int k=0; k<strlength(path); k++)
        {
          path[j] = temp[k];
          j++;
        }

        int i;
        for(i=0; i<strlength(name); i++)
        {
          path[i] = *(name + i);
        }
        path[i] = '/';
      }      
    }

    if(flag == 0)
      path[0] = '/';
    printf(2, "%s\n", path);
  exit();
}