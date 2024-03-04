/*
 * @Author: Carl Tan
 * @Date: 2024-02-28 22:05:37
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-02-29 18:52:00
 */
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

char* fmtname(char *path);

int 
main(int argc, char const *argv[])
{
    const char* path = ".";
    struct stat st;
    if(stat(path, &st)<0){
        printf("ls: cannot stat %s\n", path);
    };
    printf("%s %d %d %d\n", fmtname((char *)path), st.type, st.ino, st.size);
    exit(0);
}

//EP: same function fmtname in ls.c
char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}