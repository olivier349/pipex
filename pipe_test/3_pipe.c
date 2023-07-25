#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int ft_strlen(const char *str)
{
    int i;
    while (*str)
        i++; 
    return (i);
}

int main(void)
{
    int fd_pipe[2];
    char buf[5];
    char *pin;
    if(pipe(fd_pipe) == -1)
    {
        perror("exit");
        exit(EXIT_FAILURE);
    }
    // Tout d'abord, j'ai créé un processus enfant en utilisant la fonction fork().
    pid_t pid = fork();
    if (pid == 0)// in child processe
    {
        // Ensuite, dans le processus enfant ( pid == 0 ),
        //  j'ai écrit le code PIN dans le tube à l'aide de la fonction write() .
        pin = "4821\0";//pin to send
        close(fd_pipe[0]);//close read fd[0]
        write(fd_pipe[1], pin, 5);//write pin to pipe
        printf ( "Génération du code PIN dans l'enfant et envoi au parent... \n ");
        sleep(2);//desplay
        exit(EXIT_SUCCESS);
    }
    
    if (pid > 0)
    {
        // Une fois que le code PIN est écrit dans le tube à partir du processus enfant, 
        // le processus parent ( pid > 0 ) le lit à partir du tube à l'aide de la fonction read() .
        wait(NULL);
        close(fd_pipe[1]);// vu que le pipe[1] etpour la lecture on ferme l'ecriture donc la sorti fd[1]
        read(fd_pipe[0], buf,5);// read for pipe
        close(fd_pipe[0]);// close pipe
        // Ensuite, le processus parent a imprimé le code PIN en utilisant la fonction printf() comme d'habitude.
        printf("parent received pin '%s'\n",buf);
    }
    return EXIT_SUCCESS;
}


