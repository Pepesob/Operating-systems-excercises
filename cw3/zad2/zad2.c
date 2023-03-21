#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv){
    if (argc != 2){
        printf("Wrong number of arguments!\n");
    }

    char* path = argv[1];
    char* name = &argv[0][2];
    setbuf(stdout, NULL);

    printf("%s\t", name);

    int error = execl("/bin/ls",name, path,NULL);
    printf("Error with ls function! %d\n", error);
    return 0;
}