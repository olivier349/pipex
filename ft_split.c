/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliove <olivierliove@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:55:12 by oliove            #+#    #+#             */
/*   Updated: 2023/07/25 02:58:45 by oliove           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/util.h"

static int	ft_word_count(char const *s, char car)
{
    int i;
    int j;
    char c;
    
    i = 0;
    j = 0;
    c = car;
    while (s[i] != '\0')
    {
        if (c == car && s[i] != c)
            j++;
        c = s[i];
        i++;
    }
    return (j);
}
static char *ft_free_sub(char *str)
{
    free(str);
    return (NULL);    
}
static char *ft_substr_mod(char const *s, unsigned int start, size_t len)
{
    int i;
    int j;
    char *dest;

    i = 0;
    j = 0;
    if (!s)
        return (NULL);
    if (len > ft_strlen(s) - start)
        len = ft_strlen(s) - start;
    if(start > (unsigned int)ft_strlen(s))
        len = 0;
    dest = malloc(sizeof(char) * (len + 1));
    if(!dest)
        return(ft_free_sub(dest));
    while (s[i])
    {
        if (i >= (int)start && j < (int)len)
            dest[j++] = s[i];
        i++;    
    }
    dest[j] = '\0';
    return (dest);
}
static void *ft_free(char **tab, int w)
{
    int i;

    i = 0;
    while(i != w)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (NULL);
}
char	**ft_split(char const *s, char c)
{
    char    **tab;
    int     i;
    int     j;
    int     w;
    
    i = 0;
    j = 0;
    w = 0;
    tab = (char **)malloc(sizeof(char *) * (ft_word_count(s,c) + 1));
    if(!tab)
        return (NULL);
    while (s[i] && s[j] && w < ft_word_count(s,c))
    {
       i = j;
        while (s[i] && s[i] == c)
            i++;
        j = i;
        while(s[j] && s[j] != c)
            j++;
        tab[w++] = ft_substr_mod(s,i,j - i);
        if (!tab[w - 1])
            return(ft_free(tab,w));
        tab[w] = NULL;
    }
    return (tab);    
}
