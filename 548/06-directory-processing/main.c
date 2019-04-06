#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

//struct dirent {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported by all file system types */
//    char           d_name[256]; /* filename */
//};

//DIR *opendir(const char *name);
//int closedir(DIR *dirp);

//struct dirent *readdir(DIR *dirp);
//int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("/");
    if (!dir) {
        perror("diropen");
        exit(1);
    };

    while ( (entry = readdir(dir)) != NULL ) {
        printf("%d - %s [%d] %d\n", entry->d_ino, entry->d_name, entry->d_type, entry->d_reclen);
    };

    closedir(dir);
}
