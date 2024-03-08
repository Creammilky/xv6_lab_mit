/*
 * @Author: Carl Tan
 * @Date: 2024-02-26 19:19:08
 * @LastEditors: Carl Tan
 * @LastEditTime: 2024-02-29 18:22:37
 */
#define T_DIR     1   // Directory
#define T_FILE    2   // File
#define T_DEVICE  3   // Device

struct stat {
  int dev;     // File system's disk device
  uint ino;    // Inode number
  short type;  // Type of file
  short nlink; // Number of links to file
  uint64 size; // Size of file in bytes
};
