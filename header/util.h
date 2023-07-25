#ifndef UTIL_H
#define UTIL_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>


int ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char    *ft_strjoin(char const *s1, char const *s2 );
void    ft_path_dir(char **cmd);

#endif