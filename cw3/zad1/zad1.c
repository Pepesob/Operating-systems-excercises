#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char** argv){
    if (argc != 2){
        printf("Wrong number of arguments!\n");
        return 0;
    }
    char* end;
    int num = strtol(argv[1],&end,10);
    if (end[0] != '\0'){
        printf("Wrong argument!\n"); fflush(stdout);
        return 0;
    }

    pid_t child_pid;
    pid_t own_pid;
    pid_t parent_pid;
    for (int i = 0; i < num; i++){
        child_pid = fork();
        parent_pid = getppid();
        if (child_pid == 0){
            own_pid = getpid();
            printf("Parent pid: %d    Own pid: %d\n", parent_pid, own_pid);
            fflush(stdout);
            return 0;
        }
    }
    while (wait(0) > 0);
    printf("Number of processes: %d\n", num); fflush(stdout);
    return 0;
}