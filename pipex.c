/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:47:43 by oliove            #+#    #+#             */
/*   Updated: 2023/07/26 01:23:57 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "header/util.h"
//getenv
int main(int ac, char **av, char **env)
{
    if(ac < 5)
        return 1;
    t_pipe p;
    p.file1 = av[1];
    p.cmd1 = ft_split(av[2],' ');
    p.cmd2 = ft_split(av[3], ' ');
    p.file2 = av[4];
   
    ft_path_dir(p.cmd1);
    ft_path_dir(p.cmd2);
    if (pipe(p.fd_pipe) == -1)
        ft_error("pipe");
    pid_t pid1;
    pid1 = fork();
    if (pid1 == -1)
        ft_error("fork");
    if (pid1 == 0)
        ft_father(p.file1, p.fd_pipe, p.cmd1, env);
    pid_t pid2 = fork();
    if (pid2 == -1)
        ft_error("fork");
    if (pid2 == 0)// processus enfant 2(cmd2)
        ft_child(p.file2, p.fd_pipe, p.cmd2, env);
    close(p.fd_pipe[0]);
    close(p.fd_pipe[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    return EXIT_SUCCESS; 
}
