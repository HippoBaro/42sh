/*
** my_path_to_tab.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:54:02 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:54:03 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	pathCount(char *str)
{
  int		i;
  int		out;

  i = 0;
  out = 0;
  while (str[i] != '\0' && str[i] != '\n')
    {
      if (str[i] == ':')
	out++;
      i++;
    }
  out++;
  return (out);
}

static int	charCount(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0' && str[i] != ':')
    i++;
  return (i);
}

char		**pathToArray(char *str)
{
  int		i;
  int		j;
  int		l;
  char		**out;

  i = 0;
  l = 0;
  if (!(out = xmalloc((pathCount(str) + 1) * sizeof(*out))))
    return (NULL);
  while (str[i] != '\0' && l < pathCount(str))
    {
      j = 0;
      if (!(out[l] = xmalloc((charCount(&str[i]) + 1) * sizeof(**out))))
	return (NULL);
      while (str[i] != ':' && str[i] != '\0')
	out[l][j++] = str[i++];
      out[l][j] = '\0';
      if (str[i] != '\0')
	i++;
      l++;
    }
  out[l] = NULL;
  return (out);
}
