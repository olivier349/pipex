#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// Data written to fildes[1] appears on (i.e., can be read from) fildes[0]. == pipe
// fork
// dup2
//  exe_ve
// STDIN_FILENO
// STDOUT_FILENO

// int ft_strlen(char *str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i] != '\0')
// 		i++;
// 	return(i);
// }

void	write_str(int fd, const char *str)
{
	write(fd, str, ft_strlen(str));
}




int main(int ac, char **av)
{
      
    int    pipe_fd[2];//stock fd du pipe
                // pipe[0] lecture seul
                // pipe[1] ecriture seul
    pid_t pid; // stock le retour de fock 
    char buf[3000];//stock le retour de read

    // creer un pipe, si erreur on arrete tout 
    if(pipe(pipe_fd))
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork;
    if (pid == -1)
    {
        perror("pip");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)// creer un processus fils
    {
        //ferme bout le bout d'ecritureinutiliser 
        close(pipe_fd[1]);
        write_str(STDOUT_FILENO,"Fils : quel est ton secret ?\n");
        write_str(STDOUT_FILENO,"Fils : \"");

        // lis chaque caractere un a un
        while (read(pipe_fd[0], &buf, 1) > 0)
        {
            write(STDOUT_FILENO, &buf, 1);//ecrie le caractere lu dans la sortie standar
        }
        write_str(STDOUT_FILENO,"\"");
        write_str(STDOUT_FILENO,"Fils : je vais voir mon pere \n");
        // ferme le bout de lecture
        close(pipe_fd[0]);
        exit(EXIT_SUCCESS);
    }
    else//processus pere
    {
        //ferme le bout de lecture inutiliser
        close(pipe_fd[0]);
        write_str(STDOUT_FILENO,"Pere : J'ecrit un secret sur le pipe\n");
        // ecrit dans le bout d'ecriture du pip
        write_str(STDOUT_FILENO,"\e[33mJe suis ton pere !!!!");
        //	Ferme le bout d'ecriture (lecteur verra EOF)
		close(pipefd[1]);
        //	Attend la terminaison du fils
		wait(NULL);
		writestr(STDOUT_FILENO, "Pere : Salut mon fils !\n");
		exit(EXIT_SUCCESS);
	}
}

        
 

        // pipe(fd);
        // write(fd[1],"Holalal",7);
        // int r = read(fd[0],buf,10);
        // if (r == -1)
        //     return -1;
        // buf[r] = '\0';
        // printf("%s\n", buf);
        // write(1, "lol", 3);
        // write(STDOUT_FILENO, "lol", 3);
    
