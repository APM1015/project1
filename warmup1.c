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
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int processor_count = 0;

    FILE *filePath = fopen("/proc/cpuinfo", "r");

    if (filePath == NULL) {
        exit(EXIT_FAILURE);
    }
    

    while ((read = getline(&line, &len, filePath)) != -1) {
        if (strncmp(line, "processor", 8) == 0) {
            processor_count++;
        }
        if (strncmp(line, "cache size", 10) == 0){
            printf("cache in CPU: %s\n", line + 13);
        }
    }
    fclose(filePath);
    printf("Total number of processors: %d\n", processor_count);

}
