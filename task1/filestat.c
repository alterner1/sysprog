#include <dirent.h> 
#include <stdio.h>

int main(int argc, char* argv[]) {

  DIR *d;
  struct dirent *dir;
  if (argc > 1) {
    char *path = argv[1];
    d = opendir(path);
 
 
    if (d == NULL) {
        printf("Point correct directory name instead of: %s \n", path);
        return 1;
    }


    int ftypes[] = {0, 0, 0, 0, 0, 0, 0, 0};
    if (d) {
      while ((dir = readdir(d)) != NULL) {
        if (dir ->d_type == DT_REG) {
         ftypes[0]++;   //- -regular file
        }
        else if (dir ->d_type == DT_DIR) {
         ftypes[1]++;   //d -directory
        }
        else if (dir ->d_type == DT_LNK) {
         ftypes[2]++;   //l -symbolic link
        }
        else if (dir ->d_type == DT_FIFO) {
         ftypes[3]++;   //p -named pipe
        }
        else if (dir ->d_type == DT_SOCK) {
         ftypes[4]++;   //s -socket
        }
        else if (dir ->d_type == DT_BLK) {
         ftypes[5]++;   //b -block device
         }
         else if (dir ->d_type == DT_CHR) {
         ftypes[6]++;   //c -character device
         }
         else {
         ftypes[7]++;   // -unknown
         }
        //printf("%s\n", dir->d_name);
      }
      closedir(d);
    printf("File statistics for directory %s:\n", path);
    printf("Regular files:     %6d\n", ftypes[0]);
    printf("Directories:       %6d\n", ftypes[1]);
    printf("Symbolic links:    %6d\n", ftypes[2]);
    printf("Named pipes:       %6d\n", ftypes[3]);
    printf("Sockets:           %6d\n", ftypes[4]);
    printf("Block devices:     %6d\n", ftypes[5]);
    printf("Character devices: %6d\n", ftypes[6]);
    printf("Unknowns:          %6d\n", ftypes[7]);

    }
    return(0);
  }
  else
    {
    printf("Point directory to filestat!\n");
    return 1;
    }
  
}