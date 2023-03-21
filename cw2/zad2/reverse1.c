#include <stdio.h>
#include <bits/types/struct_timespec.h>
#include <sys/times.h>
#include <stdlib.h>
#include <time.h>


void rev(char* input_file, char* output_file){
    FILE* input = fopen(input_file, "r");
    FILE* output = fopen(output_file, "w");

    if (input == NULL){
        printf("Error with input file!\n");
        exit(-2);
    }
    if (output == NULL) {
        printf("Error with output file!\n");
        exit(-3);
    }

    int check = fseek(input,-1,SEEK_END);
    char buff[2];
    fread(buff,sizeof(char), 1, input);
    if (buff[0] == '\n'){
        check = fseek(input,-2,SEEK_END);
    }
    else {
        check = fseek(input,-1,SEEK_END);
    }

    while (check >= 0){
        fread(buff,sizeof(char), 1, input);
        fwrite(buff,sizeof(char), 1,output);
        check = fseek(input, -1*2, SEEK_CUR);
    }
    //fwrite("\n",sizeof(char), 1,output);

    fclose(input);
    fclose(output);
}


int main(int argc, char** argv){
    if (argc != 3){
        printf("Wrong number of arguments!\n");
        return -1;
    }

    char* input_file = argv[1];
    char* output_file = argv[2];

    struct timespec timespec_start, timespec_end;
    struct tms tms_start, tms_end;

    clock_gettime(CLOCK_REALTIME, &timespec_start);
    times(&tms_start);
    rev(input_file, output_file);
    clock_gettime(CLOCK_REALTIME, &timespec_end);
    times(&tms_end);


    printf("Time with copying one by one:\n");
    printf("Real time: %ld ns\n",timespec_end.tv_nsec - timespec_start.tv_nsec);
    printf("System time: %ld ticks\n", tms_end.tms_cstime - tms_start.tms_cstime);
    printf("User time: %ld ticks\n", tms_end.tms_cutime - tms_start.tms_cutime);


    return 0;
}