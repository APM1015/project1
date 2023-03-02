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


    char buf[1024];
    int i = 0;
    int count = 0;
    //read teh file
    while (fgets(buf, 1024, filePath) != NULL) {
        if(buf[i] == 1){ //free mem is 2nd so print the 2nd
            printf("%s\n", buf[i]);
        }
        count++;//counting the buffers
    }
    printf("number of memory buffers: %d", count);
    // Close file
    fclose(filePath);
}
