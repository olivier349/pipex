/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:54:40 by oliove            #+#    #+#             */
/*   Updated: 2023/07/25 23:40:00 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/util.h"
void    ft_path_dir(char **cmd)
{
    int i;
    char **path_directo;
    char *path = getenv("PATH"); 
    char *name;    
    char *tmp;

    i = -1;
    if (path == NULL || cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
        return;
    path_directo = ft_split(path,':');
    while (path_directo[++i] != NULL)
    {
        tmp = ft_strjoin(path_directo[i], "/");
        name = ft_strjoin(tmp,cmd[0]);
        free(tmp);
        if(access(name,F_OK) == 0)
        {
            i = 0;
            while (path_directo[i])
                free(path_directo[i++]);
            free(cmd[0]);
            cmd[0] = name;
            return;
        }
        free(name);
    }    
}
