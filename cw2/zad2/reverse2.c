#include <stdio.h>
#include <bits/types/struct_timespec.h>
#include <sys/times.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define BUFF_SIZE 1024


void string_reverse(const char* source, char* dest, int n){
    for (int i = 0; i<n;i++){
        dest[i] = source[n-1-i];
    }
}


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

    char buff[BUFF_SIZE];
    char reversed[BUFF_SIZE];

    fseek(input,0,SEEK_END);

    int file_size = ftell(input);
    int num_blocks = file_size / BUFF_SIZE;
    int remainder = file_size % BUFF_SIZE;

    int bytes_read;

    fseek(input,-BUFF_SIZE,SEEK_END);
    bytes_read = fread(buff, sizeof(char),BUFF_SIZE,input);
    if(buff[bytes_read-1] == '\n'){
        bytes_read--;
    }
    string_reverse(buff, reversed, bytes_read);
    fwrite(reversed,sizeof(char),bytes_read,output);

    for (int i = 1; i < num_blocks; i++) {
        fseek(input, -2*BUFF_SIZE, SEEK_CUR);
        fread(buff, sizeof(char), BUFF_SIZE, input);
        string_reverse(buff, reversed, bytes_read);
        fwrite(reversed,sizeof(char),BUFF_SIZE,output);
    }

    if (remainder > 0) {
        fseek(input, 0, SEEK_SET);
        fread(buff, sizeof(char), remainder, input);
        string_reverse(buff, reversed, remainder);
        fwrite(reversed,sizeof(char),remainder,output);
    }

    //fwrite("\n",sizeof(char),1,output);

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


    printf("Time with copying blocks:\n");
    printf("Real time: %ld ns\n",timespec_end.tv_nsec - timespec_start.tv_nsec);
    printf("System time: %ld ticks\n", tms_end.tms_cstime - tms_start.tms_cstime);
    printf("User time: %ld ticks\n", tms_end.tms_cutime - tms_start.tms_cutime);


    return 0;
}