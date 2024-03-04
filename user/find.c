/*
 * @Author: Carl Tan
 * @Date: 2024-02-29 18:29:02
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-03-02 18:27:42
 */
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(const char *path, const char *file);

int 
main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        fprintf(2, "usage: find [root_path] <file_name>");
    }
    else if (argc == 2)
    {
        find(".", argv[1]);
    }
    else
    {
        find(argv[1], argv[2]);
    }
    exit(0);
}

void 
find(const char *path, const char *file)
{
    int fd;
    struct dirent de;
    struct stat st;
    char buf[512], *p;

    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
    { // EP: DIRSIZ is max len of <file>name, adding path and 2 len of '\0'  must not excced buflen.
        fprintf(2, "ls: path too long\n");
        return;
    }
    else
    {
        if ((fd = open(path, O_RDONLY)) < 0)  //EP: get current path's fd
        {
            fprintf(2, "ls: cannot open %s\n", path);
            return;
        }
        // EP: serialize base dir to "path/"
        strcpy(buf, path);
        p = buf + strlen(path);
        *p++ = '/';
    }

    while (read(fd, &de, sizeof(de)) == sizeof(de)) //EP: get each dirent
    {
        if (de.inum == 0)
            continue;
        // EP: get each PATH to accquire stat by stat()
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0; // EP£ºSet end of buf '\0'.qui
        if (stat(buf, &st) < 0)
        { // EP: stat(const char *path_file, struct stat *st)£¬find file and serialize its info to st.
            printf("ls: cannot stat %s\n", buf);
            continue;
        }
        if (!strcmp(de.name, file) && st.type == T_FILE)
        {
            printf("%s\n", buf); // EP: print full PATH
            memset(p, 0, DIRSIZ); // EP: not so vital becluse of line 62
        }
        else if (st.type == T_DIR && !!strcmp(de.name, ".") && !!strcmp(de.name, ".."))
        {
            find(buf, file);
        }
    }
    return;
}
