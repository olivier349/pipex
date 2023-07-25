/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/07/25 23:43:47 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header/util.h"
//getenv
int main(int ac, char **av, char **env)
{
    char *path = getenv("PATH"); 
    printf("%s\n",path);
    if(ac < 5)
        return 1;
    char *file1 = av[1];
    char **cmd1 = ft_split(av[2],' ');
    char **cmd2 = ft_split(av[3], ' ');
    char *file2 = av[4];
    ft_path_dir(cmd1);
    ft_path_dir(cmd2);
    
    for (int i = 0; cmd1[i] ;i++)
    {
        printf("cmd1 : %s\n",cmd1[i]);
    }
    
    for (int i = 0; cmd2[i] ;i++)
    {
        printf("cmd2 : %s\n",cmd2[i]);
    }
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
        for (int i = 0; cmd1[i]; i++)
            printf("cmd1[%d] = %s\n", i, cmd1[i]);
        dup2(fd1, STDIN_FILENO);
        close(fd1);
        close(fd_pipe[0]);

        dup2(fd_pipe[1],STDOUT_FILENO);
        close(fd_pipe[1]);

        // char *cmd1_args[] = {cmd1, NULL};
        execve(cmd1[0], cmd1,env);
        
        perror("execve cmd1");
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
        dup2(fd_pipe[0], STDIN_FILENO);
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
        // char *cmd2_args[] = {cmd2,NULL};
        execve(cmd2[0],cmd2,env);

        // en cas d'erreur, perror affiche le message d'erreur appropie
        perror("execve cmd2");
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