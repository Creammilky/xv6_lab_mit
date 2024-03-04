/*
 * @Author: Carl Tan
 * @Date: 2024-02-26 19:19:46
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-02-28 21:42:17
 */
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(2, "usage: sleep <time>\n");
        exit(1);
    }
    if(atoi(argv[1]) >= 0){
        sleep(atoi(argv[1]));
    }
    else{
        fprintf(2, "usage: sleep time must be positive\n");
        exit(1);
    }
    exit(0);
}
