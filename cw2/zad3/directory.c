#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stats;
    long long total_size = 0;

    dir = opendir(".");
    if (dir == NULL) {
        printf("Error: could not open directory.\n");
        exit(1);
    }

    while ((entry = readdir(dir)) != NULL) {
        stat(entry->d_name, &file_stats);

        if (!S_ISDIR(file_stats.st_mode)) {
            printf("%ld    %s\n", file_stats.st_size, entry->d_name);
            total_size += file_stats.st_size;
        }
    }

    closedir(dir);

    printf("%lld total\n", total_size);

    return 0;
}