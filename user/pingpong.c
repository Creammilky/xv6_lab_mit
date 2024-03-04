/*
 * @Author: Carl Tan
 * @Date: 2024-02-28 21:07:54
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-02-28 22:04:36
 */
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    int p[2]; // pipe
    printf("Info: Parent's pid is %d\n\n", getpid());
    pipe(p);
    const char *parent_ping = "p";
    const char *child_ping = "q";
    write(p[1], parent_ping, 1);
    if (fork() == 0)
    {
        printf("Info: Child's pid is %d\n\n", getpid());
        char *msg = (char *)malloc(sizeof(char));
        read(p[0], msg, 1);
        if (!memcmp(msg, "p", 1))
        {
            printf("%d: received ping\n", getpid());
        }
        write(p[1], child_ping, 1);
        exit(0);
        
    }
    else
    {
        wait((int *)0);
        char *msg = (char *)malloc(sizeof(char));
        read(p[0], msg, 1);
        if (!memcmp(msg, "q", 1))
        {
            printf("%d: received pong\n", getpid());
        }
    }
    exit(0);
}