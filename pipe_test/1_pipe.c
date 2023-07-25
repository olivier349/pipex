#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int fd_pipe[2];//declaration des pipe
    if (pipe(fd_pipe) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    printf("lis la vaeur du descripteur du fichier : %d\n",fd_pipe[0]);
    printf("ecrie la valeur du descripteur de fichier : %d\n",fd_pipe[1]);
    return (EXIT_SUCCESS);
}