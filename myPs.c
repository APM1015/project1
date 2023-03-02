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
#include <stdbool.h>

int pid(const char *string);
int systemTime(char *string, int pid);
int state(char *string, int pid);
int commandLine(char *string, int pid);
int uTime(char *argv, int pid);
int virtMemory(char *argv, int pid);

bool s = false;
bool c = true;
bool v = false;
bool U = true;
bool S = true;

int main(int argc, char *argv[]) {
    pid_t *pid = getpid();

     if(argc < 2){
         perror("Error: Invalid Number of arguments");
         exit(EXIT_FAILURE);
     }
    int opt = 0;
    while ((opt = getopt(argc, argv, "psUSvc")) != -1) {
        switch (opt) {
            //  case '-p':    // file
            //  pid(argv[i]);
            //   break;
            case 's':    // field separator
                s = !s;
                break;
            case 'U':    // variable assignment
                U = !U;
                break;
            case 'S':    // extension
                S = !S;
                break;
            case 'v':    // extension
                v = !v;
                break;
            case 'c':    // extension
                c = !c;
                break;
            default:
                //printf("p = %d   ", pid);
                break;
        }

    }
    printf("p = %d   ", pid);
    if(s){
        state(*argv, pid);
    }
    if(U){
        uTime(argv, pid);
    }
    if(S){
        systemTime(argv, pid);
    }
    if(v){
        virtMemory(argv, pid);
    }
    if(c){
        commandLine(argv, pid);
    }

    printf("\n");
    return 0;
}

//-p
int pid(const char *argv) {
    //int pid = getpid(argv[1]);
    //printf("%d", &pid);
   // return 0;

    return 0;
}

//-s
int state(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
    char buf[1024];
    if(fgets(buf, 1024, f) == NULL){
        printf("Unable to open file2");
        return 1;
    }
    fclose(f);

    token = strtok(buf, " ");
    // Walk through other tokens
    while( token != NULL )
    {
        //status in 3rd position of stat
        if(i == 2){
            printf("s = %s    ", token);
            break;
        }
        str[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return 0;
}
//-S
int systemTime(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
    char buf[1024];
    if(fgets(buf, 1024, f) == NULL){
        printf("Unable to open file2");
        return 1;
    }
    fclose(f);

    // Get first token
    token = strtok(buf, " ");
   // printf("Token: %s\n", token);

    // Walk through other tokens
    while( token != NULL )
    {
        //systemTime is 10th position of stat
        if(i == 9){
            printf("S = %s    ", token);
        }
        str[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return 0;
}

//-U
int uTime(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
    char buf[1024];
    if(fgets(buf, 1024, f) == NULL){
        printf("Unable to open file2");
        return 1;
    }
    fclose(f);

    // Get first token
    token = strtok(buf, " ");
    //printf("Token: %s\n", token);

    // Walk through other tokens
    while( token != NULL )
    {
        //utime in 14th position of stat
        if(i == 13){
            printf("U = %s    ", token);
        }
        str[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return 0;
}

//-v
int virtMemory(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/statm", pid);

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
    char buf[1024];
    if(fgets(buf, 1024, f) == NULL){
        printf("Unable to open file2");
        return 1;
    }
    fclose(f);

    // Get first token
    token = strtok(buf, " ");

    // Walk through other tokens
    while( token != NULL )
    {
        //virtual time size in 1st position of statm
        if(i == 0){
            printf("v = %d    ", token);
        }
        str[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return 0;
}

//-c
int commandLine(char *argv, int pid){
    char cmndline[1024];
    int l;

    char filename[1024];
    sprintf(filename, "/proc/%d/cmdline", pid);
    FILE *f = fopen(filename, "r");
    
    if(f == NULL){
        printf("Unable to open file");
        return 1;
    }
    if(f){
        l = fread(cmndline, 1, 1024 -1, f);
        if(l > 0){
            for(int i = 0; i < l; i++){
                if(cmndline[i] == '\0'){
                    cmndline[i] = ' ';
                }
            }
            printf("c = %s    ", cmndline);
        }
    }
    //char cmdline;
    //fscanf(f, "%c", &cmndline);
    //fgets(cmndline, 500, f);
    fclose(f);

    //printf("c = %s    \n", cmdline);
    //return 0;



    return 0;
}
