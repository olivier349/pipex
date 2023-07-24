#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>




int main(int ac, char **av)
{
    if(ac < 5)
        return 1;
    
    char *file1 = av[1];
    char *cmd1 = av[2];
    char *cmd2 = av[3];
    char *file2 = av[4];
    
    int fd_pipe[2];
    if (pipe(fd_pipe) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid1;
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0)
    {
        int fd1 = open(file1,O_RDONLY);
        if (fd1 == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd1, STDIN_FILENO);
        close(fd1);
        close(fd_pipe[0]);

        dup2(fd_pipe[1],STDOUT_FILENO);
        close(fd_pipe[1]);

        char *cmd1_args[] = {cmd1, NULL};
        execvp(cmd1, cmd1_args);
        
        perror("execvp cmd1");
        return 1;
    }


    pid_t pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid2 == 0)// processus enfant 2(cmd2)
    {
        // ferme l'extremite d'ecriture du tube(inutiliser dans ce processus)
        close(fd_pipe[1]);
        int fd2 = open(file2,O_WRONLY | O_CREAT |O_TRUNC,0666);
        if(fd2 == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }
        dup2(fd2,STDOUT_FILENO);
        close(fd2);
        // execute cmd2 dans le processuse enfant en remplacant son imagepar celle de cmd2
        char *cmd2_args[] = {cmd2,NULL};
        execvp(cmd2,cmd2_args);

        // en cas d'erreur, perror affiche le message d'erreur appropie
        perror("execvp cmd2");
        return 1;
        
    }
    //fermer les extremiter de tube qui ne son pas utilisees dans les processus enfant
    close(fd_pipe[0]);
    close(fd_pipe[1]);

    //attendre que les deux processus enfant se terminent
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    return EXIT_SUCCESS; 
}