/*
 * @Author: Carl Tan
 * @Date: 2024-02-28 20:05:24
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-02-28 21:41:23
 */
#include"kernel/types.h"
#include"user/user.h"

int 
main(int argc, char const *argv[])
{
    if(fork()==0){
        fprintf(1, "Standard output of child process\n");
        //close(1);  //Comment here to see whether father & child's fd are irrelevant.
        fprintf(1, "trying child process stdo again\n");
    }
    else{
        wait((int *)0);
        fprintf(1, "Standard output of father process\n");
        printf("Finished.\n");
    }
    fprintf(1, "Some process is about to end\n\n");
    exit(0);
}

/* Before Comment
$ fdtest
Standard output of child process
Standard output of father process
Finished.
Some process is \about to end

*/

/* After Comment
$ fdtest
Standard output of child process
trying child process stdo again
Some process is about to end

Standard output of father process
Finished.
Some process is about to end

*/