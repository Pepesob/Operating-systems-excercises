#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 1024


int check_input(int argc, char** argv){
    if (argc != 5){
        printf("Wrong number of arguments!\n");
        return -5;
    }
    if (strlen(argv[1]) != 1){
        printf("Wrong first argument!\n");
        return -1;
    }
    if (strlen(argv[2]) != 1){
        printf("Wrong second argument!\n");
        return -2;
    }
    return 0;
}

void change_letter(const char* src, char* dest, int n, char to_find, char to_swap){
    for (int i = n-1; i >= 0; i--){
        if (src[i] == to_find){
            dest[i] = to_swap;
        }
        else {
            dest[i] = src[i];
        }
    }
}


void f_swap_and_write(FILE* input, FILE* output, char to_find, char to_swap){
    char buff[BUFF_SIZE];
    char changed[BUFF_SIZE];
    size_t bytes_read;
    bytes_read = fread(buff, sizeof(char), BUFF_SIZE, input);
    printf("%ld\n", bytes_read);
    while (bytes_read){
        change_letter(buff, changed,bytes_read, to_find, to_swap);
        fwrite(changed, sizeof(char), bytes_read, output);
        bytes_read = fread(buff, sizeof(char), BUFF_SIZE, input);
    }
}


void second_variant(char to_find, char to_swap, const char* input_file, const char* output_file){
    FILE *input, *output;
    input = fopen(input_file, "r");
    output = fopen(output_file, "w");

    if (input == NULL) {
        printf("Input file does not exist or error with opening!\n");
        exit(-8);
    }
    if (output == NULL) {
        printf("Error with output file!\n");
        exit(-9);
    }

    f_swap_and_write(input, output, to_find, to_swap);

    fclose(input);
    fclose(output);
}


int main(int argc, char** argv) {
    int status = check_input(argc, argv);
    if (status != 0){
        exit(status);
    }

    struct timespec timespec_start_s, timespec_end_s;
    struct tms tms_start_s, tms_end_s;

    char to_find = argv[1][0];
    char to_swap = argv[2][0];
    char* input_file = argv[3];
    char* output_file = argv[4];


    clock_gettime(CLOCK_REALTIME, &timespec_start_s);
    times(&tms_start_s);
    second_variant(to_find,to_swap,input_file,output_file);
    clock_gettime(CLOCK_REALTIME, &timespec_end_s);
    times(&tms_end_s);


    printf("Time with library functions:\n");
    printf("Real time: %ld ns\n",timespec_end_s.tv_nsec - timespec_start_s.tv_nsec);
    printf("System time: %ld ticks\n", tms_end_s.tms_cstime - tms_start_s.tms_cstime);
    printf("User time: %ld ticks\n", tms_end_s.tms_cutime - tms_start_s.tms_cutime);

    return 0;
}
