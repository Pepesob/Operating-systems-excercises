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


void swap_and_write(int input_descriptor, int output_descriptor, char to_find, char to_swap){
    char buff[BUFF_SIZE];
    char rev[BUFF_SIZE];
    ssize_t bytes_read;
    bytes_read = read(input_descriptor, buff, BUFF_SIZE);
    while (bytes_read){
        change_letter(buff, rev,bytes_read, to_find, to_swap);
        write(output_descriptor, rev, bytes_read);
        bytes_read = read(input_descriptor, buff, BUFF_SIZE);
    }
}


void first_variant(char to_find, char to_swap, const char* input_file, const char* output_file){
    int input_descriptor = open(input_file,O_RDONLY);
    int output_descriptor = open(output_file, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);

    if (input_descriptor < 0) {
        printf("Input file does not exist or error with opening!\n");
        exit(-6);
    }
    if (output_descriptor < 0) {
        printf("Error with output file!\n");
        exit(-7);
    }

    swap_and_write(input_descriptor, output_descriptor, to_find, to_swap);
    close(input_descriptor);
    close(output_descriptor);
}


int main(int argc, char** argv) {
    int status = check_input(argc, argv);
    if (status != 0){
        exit(status);
    }

    struct timespec timespec_start_f, timespec_end_f;
    struct tms tms_start_f, tms_end_f;

    char to_find = argv[1][0];
    char to_swap = argv[2][0];
    char* input_file = argv[3];
    char* output_file = argv[4];


    clock_gettime(CLOCK_REALTIME, &timespec_start_f);
    times(&tms_start_f);
    first_variant(to_find, to_swap, input_file, output_file);
    clock_gettime(CLOCK_REALTIME, &timespec_end_f);
    times(&tms_end_f);


    printf("Time with system functions:\n");
    printf("Real time: %ld ns\n",timespec_end_f.tv_nsec - timespec_start_f.tv_nsec);
    printf("System time: %ld ticks\n", tms_end_f.tms_cstime - tms_start_f.tms_cstime);
    printf("User time: %ld ticks\n", tms_end_f.tms_cutime - tms_start_f.tms_cutime);
    return 0;
}
