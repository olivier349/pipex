#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

typedef struct s_pipe
{
     char *file1;
    char **cmd1;
    char **cmd2;
    char *file2;
    int fd_pipe[2]; 
}               t_pipe;


int     ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char    *ft_strjoin(char const *s1, char const *s2 );
void    ft_path_dir(char **cmd);
int     ft_father(char *file, int *fd_pipe,char **cmd, char **env);
int     ft_child(char *file,int *fd_pipe,char **cmd2,char **env);
void    ft_error(char *str);

#endif