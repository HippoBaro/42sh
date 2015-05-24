/*
** my_strdup.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:58:48 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:58:49 2015 Hippolyte Barraud
*/

#include <42sh.h>

char	*my_strdup(char *src)
{
  char	*ret;

  if (!src)
    return (NULL);
  if (!(ret = xmalloc((my_strlen(src) + 1) * sizeof(*ret))))
    return (NULL);
  my_strcpy(ret, src);
  return (ret);
}
