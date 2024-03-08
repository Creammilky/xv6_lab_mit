/*
 * @Author: Carl Tan
 * @Date: 2024-02-26 19:19:08
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-03-02 18:27:54
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

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

void
ls(char *path)
{
  char buf[512], *p; //EP: *p is a util to modify buf(some path).
  //char buf_fdo[1024];
  int fd;
  struct dirent de; //QUES: What's this?
  struct stat st;

  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }else{
    //read(fd, buf_fdo, sizeof(buf_fdo));
    //printf(buf_fdo);
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    printf("%s %d %d %l\n", fmtname(path), st.type, st.ino, st.size);
    break;

  //EP: List all subfile in current dir
  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){  //EP: DIRSIZ is max len of <file>name, adding path and 2 len of '\0'  must not excced buflen.
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path); //EP: cp path at the start of buf
    p = buf+strlen(buf); //EP: locate the pointer after the last byte of path in buf. 
    *p++ = '/'; //EP: first let *p = '/', then p++ to move this pointer forward, namely, append a slash to entering this path.
    while(read(fd, &de, sizeof(de)) == sizeof(de)){ //EP: fd opened as path in advance.  //QUES : What's for?
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ); //EP: Critically notice, p is now pointing at buf in pos after "path/". Soit will works as strcat(memcat) to concat "path/" & "filename"
      p[DIRSIZ] = 0; // EP£ºSet end of buf '\0'.
      if(stat(buf, &st) < 0){ //EP: stat(const char *path_file, struct stat *st)£¬find file and serialize its info to st.
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
      printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size); //EP£ºprint one line of ls.
    }
    break;
  }
  close(fd);
}

int
main(int argc, char *argv[])
{
  int i;

  if(argc < 2){
    ls(".");
    exit(0);
  }
  for(i=1; i<argc; i++)
    ls(argv[i]);
  exit(0);
}
