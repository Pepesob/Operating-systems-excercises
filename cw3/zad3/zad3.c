#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFF_SIZE 256


char* start_path;
char* str;


int read_and_compare(char* path){
    int id = open(path,O_RDONLY);
    if (id < 0){
        printf("Error while opening the file\n");
    }
    int str_length = strlen(str);
    char buff[BUFF_SIZE];
    int bytes_read = read(id, buff, str_length);
    buff[bytes_read] = '\0';
    close(id);
    if(str_length != bytes_read){
        return -1;
    }
    if (strcmp(str,buff) != 0){
        return -1;
    }
    return 0;
}



void search(const char* directory_path){
    DIR* direct = opendir(directory_path);
    if (direct == NULL){
        perror(directory_path);
        return;
    }
    struct dirent* entry;
    struct stat file_stats;

    pid_t curr_pid = getpid();

    char path_to_file[PATH_MAX];

    while ((entry = readdir(direct)) != NULL){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        snprintf(path_to_file, PATH_MAX,"%s/%s", directory_path, entry->d_name);
        if (stat(path_to_file, &file_stats) != 0){
            printf("Error while reading statistics of the file %s!\n", path_to_file);
            continue;
        }
        if (S_ISDIR(file_stats.st_mode)){
            pid_t child_pid = fork();
            if (child_pid == 0) {
                search(path_to_file);
                return;
            }
        }
        else {
            if (read_and_compare(path_to_file) == 0){
                printf("File: %s, PID: %d\n", path_to_file, curr_pid);
            }
        }
    }
    closedir(direct);
}


int main(int argc, char** argv){
    if (argc != 3){
        printf("Wrong number of arguments!\n");
    }

    start_path = argv[1];
    str = argv[2];

    search(start_path);
    while (wait(0) > 0);
    return 0;
}