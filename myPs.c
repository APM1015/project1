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

//created booleans for my different functions as the regular flag from document was not working for my functions
bool s = false;
bool c = true;
bool v = false;
bool U = true;
bool S = true;

int main(int argc, char *argv[]) {
    //retrieving pid
    pid_t *pid = getpid();
    
     if(argc < 2){//error if no argument is presented
         perror("Error: Invalid Number of arguments");
         exit(EXIT_FAILURE);
     }
    int opt = 0;
    while ((opt = getopt(argc, argv, "psUSvc")) != -1) {//using getopt loop from the reading
        switch (opt) {
            //  case '-p':    
            //  pid(argv[i]);
            //   break;
            //each call flips the boolean value for the function call
            case 's':    
                s = !s;
                break;
            case 'U':    
                U = !U;
                break;
            case 'S':    
                S = !S;
                break;
            case 'v':    
                v = !v;
                break;
            case 'c':    
                c = !c;
                break;
            default:
                //printf("p = %d   ", pid);
                break;
        }

    }
    printf("p = %d   ", pid);//printing pid value
    //calling function to print if the boolean value is true
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

//-s function
int state(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid); //put /proc/stat into fileName

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r"); //reading fileName
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

    //tokenizing the /proc/stat
    token = strtok(buf, " ");
    // Go through other tokens
    while( token != NULL )
    {
        //status in 3rd position of stat so print value
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
//-S function
int systemTime(char *argv, int pid){ 
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);//Use sprintf to put /proc/stat into fileName

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r"); //reading fileName
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

    // Get token
    token = strtok(buf, " ");

    // Go through other tokens
    while( token != NULL )
    {
        //systemTime is 10th position of stat so print it out
        if(i == 9){
            printf("S = %s    ", token);
        }
        str[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return 0;
}

//-U function
int uTime(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid); //Use sprintf to put /proc/stat into fileName

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r"); //reading fileName
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

    // Get token and tokenize /proc/stat
    token = strtok(buf, " ");

    // Go through other tokens
    while( token != NULL )
    {
        //utime in 14th position of stat so print it out
        if(i == 13){
            printf("U = %s    ", token);
        }
        str[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    return 0;
}

//-v function
int virtMemory(char *argv, int pid){
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/statm", pid); //Use sprintf to put /proc/statm into fileName

    char *token;
    char *str[400];
    int i = 0;

    FILE *f = fopen(fileName,"r"); //reading fileName into *f
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

    // Get first token and tokenise /proc/statm
    token = strtok(buf, " ");

    // Go through other tokens
    while( token != NULL )
    {
        //virtual time size in 1st position of statm so print it out
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

    if(f == NULL){//error if file is NULL or error occurs
        printf("Unable to open file");
        return 1;
    }
    if(f){//if file is readible get length to go into for loop and print out cmndline
        l = fread(cmndline, 1, 1024 -1, f);
        if(l > 0){
            for(int i = 0; i < l; i++){
                //eliminate null space
                if(cmndline[i] == '\0'){
                    cmndline[i] = ' ';
                }
            }
            printf("c = %s    ", cmndline);
        }
    }
    //close file
    fclose(f);

    return 0;
}

