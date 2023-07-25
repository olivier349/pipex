/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 00:13:33 by oliove            #+#    #+#             */
/*   Updated: 2023/07/26 00:18:30 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/util.h"

int ft_father(char *file, int *fd_pipe,char **cmd, char **env)
{
    int fd1 = open(file,O_RDONLY);
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
    execve(cmd[0], cmd,env);
    perror("execve cmd1");
    return 1;
}
   