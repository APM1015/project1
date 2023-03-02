#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Open proc/meminfo file
    FILE *filePath = fopen("/proc/meminfo", "r");

    // checking if /proc/meminfo is NULL or contains an eror
    if (filePath == NULL) {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    // Read the contents of the file
    char buf[1024];
    int i = 0;
    int count = 0;
    while (fgets(buf, 1024, filePath) != NULL) {
        if(buf[i] == 1){
            printf("%s\n", buf[i]);
        }
        count++;
    }
    printf("number of memory buffers: %d", count);
    // Close file
    fclose(filePath);
}
