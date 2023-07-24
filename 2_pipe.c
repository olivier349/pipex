#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd_pipe[2];
    char buf[5];

    if(pipe(fd_pipe) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    char *pin = "4128\0";
    printf("Writing Pin to pipe.... \n");
    write(fd_pipe[1], pin, 5);
    printf("Done.\n\n");

    printf("Reading Pin from pie.... \n");
    read(fd_pipe[0], buf, 5);
    printf("Done.\n\n");

    printf("Pin from pipe %s\n", buf);
    return EXIT_SUCCESS;
}
