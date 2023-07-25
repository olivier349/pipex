#include "header/util.h"

char    *ft_strjoin(char const *s1, char const *s2 )
{
    char *res;
    int len1;
    int len2;
    int i;

    i = 0;
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    res = malloc(sizeof(char) * (len1 + len2 +1));
    if(!res)
        return(NULL);
    if(!s1 && !s2)
        return(NULL);
    while(s1[i])
    {
        res[i] = s1[i];
        i++;
    }
    i = 0;
    while (s2[i])
        res[len1++] = s2[ i++];
    res[len1] = '\0';
    return(res); 
}
