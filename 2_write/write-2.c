#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // Failure in case of insufficient amount of arguments
        fprintf(stderr, "Usage: %s filename text-to-write\n", argv[0]);
        return 1;
    }

    // Opening pointed file. rw for user, read-only for group and others
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Failed to open file for writing");
        return 2;
    }

    // Writing entered string into file
    if (dprintf(fd, "%s", argv[2]) < 0) {
        close(fd);
        perror("Failure while writing");
        return 3;
    }

    if (close(fd) < 0) {
        perror("Failure while closing fd");
        return 4;
    }

    return 0;
}