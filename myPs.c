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

int pid(const char *string);
int cpuState();
int systemTime(const char *string, int pid);
int state(const char *string, int pid);
int commandLine(const char *string, int pid);
int uTime(const char *argv, int pid);
int virtMemory(const char *argv, int pid);

int main(int argc, char *argv[]) {
    pid_t *pid = getpid();
    printf("pid = %d\n", pid);
    state(*argv, pid);
    uTime(*argv, pid);
    systemTime(*argv, pid);
    virtMemory(*argv, pid);
    commandLine(*argv, pid);


   //pid(*argv);

     //if(argc < 2){
      //   perror("Error: Invalid Number of arguments");
     //    exit(EXIT_FAILURE);
    // }

    for(int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            //pid(argv[i]);
        }

        else if(strcmp(argv[i], "-s") == 0){
            state(argv[i], pid);
        }
        else if(strcmp(argv[i], "-U") == 0){
            uTime(argv[i], pid);
        }
        else if(strcmp(argv[i], "-S") == 0){
            systemTime(argv[i], pid);
        }
        else if(strcmp(argv[i], "-v") == 0){
            virtMemory(argv[i], pid);
        }
        else if(strcmp(argv[i], "-c") == 0){
            commandLine(argv[i], pid);
        }

    }
    return (0);
}
/*
int i = 0;
while ((argc = getopt(argc, argv, "-p:-s:-U:-S:-v:-c")) != -1) {
   switch (argc) {
     //  case '-p':    // file
         //  pid(argv[i]);
        //   break;
       case '-s':    // field separator
           state(argv[i]);
           break;
       case '-U':    // variable assignment
           uTime(argv[i]);
           break;
       case '-S':    // extension
           systemTime(argv[i]);
           break;
       case '-v':    // extension
           virtMemory(argv[i]);
           break;
       case '-c':    // extension
           commandLine(argv);
           break;
       default:

           break;
   }
}
*/
//pid(argv);



//-p
int pid(const char *argv) {
    //int pid = getpid(argv[1]);
    //printf("%d", &pid);
   // return 0;


    return 0;

}

//-s
int state(const char *argv, int pid){
    //int *p = pid;
    //char procPidStat[] = "972 (docker-containe) S 901 972 972 0 -1 1077944576 2657 0 2 0 561 205 0 0 20 0 11 0 1820 441688064 2327 18446744073709551615 4194304 11049596 140727040242048 140727040241432 4602915 0 2079995941 0 2143420159 18446744073709551615 0 0 17 1 0 0 0 0 0 13147640 13322176 25554944 140727040249523 140727040249749 140727040249749 140727040249821 0";
   // char proc[] = "proc/";
    //char stat[] = "/stat";
    //strcat(proc, pid);
    //strcat(proc, stat);
    char fileName[100][100];
    //sprintf(fileName, "proc/%d/stat", pid);
    sprintf(fileName, "/proc/%d/stat", pid);

    //sprintf
    char *token;
    char *str[400];
    int i = 0;
   // char buf[1024];

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
    //fgets(str, 400, f);

    //fclose(f);

    // Get first token
    //token = strtok(f, " ");
    //printf("Token: %s\n", token);
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
            printf("s = %s\n", token);
            break;
        }
        str[i] = token;
        i++;

        token = strtok(NULL, " ");
    }
    //fclose(f);
    return 0;
}
//-S
int systemTime(const char *argv, int pid){

    // pid_t pid = getpid();
    // printf(pid);
    //char procPidStat[] = "972 (docker-containe) S 901 972 972 0 -1 1077944576 2657 0 2 0 561 205 0 0 20 0 11 0 1820 441688064 2327 18446744073709551615 4194304 11049596 140727040242048 140727040241432 4602915 0 2079995941 0 2143420159 18446744073709551615 0 0 17 1 0 0 0 0 0 13147640 13322176 25554944 140727040249523 140727040249749 140727040249749 140727040249821 0";
    //char procPidStat[] = "proc/pid/stat";
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);

    //sprintf
    char *token;
    char *str[400];
    int i = 0;
    // char buf[1024];

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
 
    fclose(f);


    // Get first token
    token = strtok(f, " ");
   // printf("Token: %s\n", token);

    // Walk through other tokens
    while( token != NULL )
    {
        //systemTime is 10th position of stat
        if(i == 9){
            printf("S = %s\n", token);
        }
        str[i] = token;
        i++;

        token = strtok(NULL, " ");
    }

    return 0;

}
//-U
int uTime(const char *argv, int pid){
    // pid_t pid = getpid();
    // printf(pid);
    //char procPidStat[] = "972 (docker-containe) S 901 972 972 0 -1 1077944576 2657 0 2 0 561 205 0 0 20 0 11 0 1820 441688064 2327 18446744073709551615 4194304 11049596 140727040242048 140727040241432 4602915 0 2079995941 0 2143420159 18446744073709551615 0 0 17 1 0 0 0 0 0 13147640 13322176 25554944 140727040249523 140727040249749 140727040249749 140727040249821 0";
    //char procPidStat[] = "proc/pid/stat";
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);

    //sprintf
    char *token;
    char *str[400];
    int i = 0;
    // char buf[1024];

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }

    fclose(f);

    // Get first token
    token = strtok(f, " ");
    //printf("Token: %s\n", token);

    // Walk through other tokens
    while( token != NULL )
    {
        //utime in 14th position of stat
        if(i == 13){
            printf("U = %s\n", token);
        }
        str[i] = token;
        i++;

        token = strtok(NULL, " ");
    }

    return 0;
}

//-v
int virtMemory(const char *argv, int pid){
    // pid_t pid = getpid();
    // printf(pid);
    //char procPidStatm[] = "27712 1928 1668 195 0 260  0";
    //char procPidStatm[] = "proc/pid/statm";
    char fileName[100][100];
    sprintf(fileName, "/proc/%d/stat", pid);

    //sprintf
    char *token;
    char *str[400];
    int i = 0;
    // char buf[1024];

    FILE *f = fopen(fileName,"r");
    if(f == NULL){
        printf("Unable to open file\n");
        return 1;
    }
  
    fclose(f);

    // Get first token
    token = strtok(f, " ");
    //printf("Token: %s\n", token);

    // Walk through other tokens
    while( token != NULL )
    {
        //virtual time size in 1st position of statm
        if(i == 0){
            printf("v = %d\n", token);
        }
        str[i] = token;
        i++;

        token = strtok(NULL, " ");
    }

    return 0;
}


//-c
int commandLine(const char *argv, int pid){
    char cmndline;

    char filename[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/cmdline", pid);
    FILE *f = fopen(filename, "rb");


    if(f == NULL){
        printf("Unable to open file");
        return 1;
    }
    char cmdline;
    fscanf(f, "%c", &cmndline);
    //fgets(cmndline, 500, f);
    fclose(f);

    printf("c = %s\n", cmdline);
    //return 0;



    return 0;
}

