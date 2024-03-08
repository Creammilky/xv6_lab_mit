#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[512];

void
cat(int fd) //fd = Opened file | stdin
{
  int n;
  //read from fd max at 512b cp it to buf and returns the num of read b's to n
  while((n = read(fd, buf, sizeof(buf))) > 0) {
    // write n b to stdout
    //stderr when read and write b not matched
    if (write(1, buf, n) != n) { 
      fprintf(2, "cat: write error\n");
      exit(1);
    }
  }
  //stderr when read b illegal
  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0); 
    exit(0);
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], O_RDONLY)) < 0){ //Open file with readonly as fd
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1); //Failed
    }
    cat(fd); // Calling cat
    close(fd); // Succeed
  }
  exit(0);
}
