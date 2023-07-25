/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    child.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:24:22 by oliove            #+#    #+#             */
/*   Updated: 2023/07/26 00:28:35 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/util.h"

int ft_child(char *file,int *fd_pipe,char **cmd2,char **env)
{
    dup2(fd_pipe[0], STDIN_FILENO);
    // ferme l'extremite d'ecriture du tube(inutiliser dans ce processus)
    close(fd_pipe[1]);
    int fd2 = open(file,O_WRONLY | O_CREAT |O_TRUNC,0666);
    if(fd2 == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(fd2,STDOUT_FILENO);
    close(fd2);
    // execute cmd2 dans le processuse enfant en remplacant son imagepar celle de cmd2
    execve(cmd2[0],cmd2,env);
    // en cas d'erreur, perror affiche le message d'erreur appropie
    perror("execve cmd2");
    return 1;
}