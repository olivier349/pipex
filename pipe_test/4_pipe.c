#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#define PIN_LENGTH 4
#define PIN_WAIT_INTERVAL 2

void get_pin(char pin[PIN_LENGTH + 1])
{
    int i;

    i = 1;
    srand(getpid() + getppid());

    pin[0] = 49 + rand() % 7;
    while (i < PIN_LENGTH)
    {
        pin[i] = 48 + rand() % 7;
        i++;
    }
    pin[PIN_LENGTH] = '\0';

}

int main(void)
{
    while (1)
    {
        int fd_pipe[2];
        char pin[PIN_LENGTH + 1];
        char buf[PIN_LENGTH + 1];

        pipe(fd_pipe);

        pid_t pid;
        pid = fork();
        // if (pipe(fd_pipe) == -1)
        // {
        //     perror("pipe");
        //     exit(EXIT_FAILURE);
        // }
        if(pid == 0)
        {
            get_pin(pin);
            close(fd_pipe[0]);
            write(fd_pipe[1], pin,PIN_LENGTH + 1);//write to pipe
            printf ( "Génération du PIN dans l'enfant et envoi au parent... \n " ) ;
            sleep(PIN_WAIT_INTERVAL);//// retarder intentionnellement la génération du code PIN.
            exit(EXIT_SUCCESS);
        }
        if (pid > 0)
        {
            wait(NULL);

            close(fd_pipe[1]);
            read(fd_pipe[0],buf,PIN_LENGTH + 1);
            close(fd_pipe[0]);
            printf ( "Le parent a reçu le code PIN '%s' de l'enfant. \n \n " , buf ) ;
        }
    }
    return EXIT_SUCCESS;
    
}