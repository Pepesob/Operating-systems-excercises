#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ftw.h>


long total_size = 0;

static int display_info(const char *fpath, const struct stat *sb, int typeflag) {
    if (typeflag == FTW_F) {
        printf("%ld    %s\n", sb->st_size, fpath);
        total_size += sb->st_size;
    }
    return 0;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong number of arguments!");
        exit(-1);
    }

    if (ftw(argv[1], display_info, 6) == -1) {
        exit(-1);
    }

    printf("%ld total\n", total_size);

    return 0;
}