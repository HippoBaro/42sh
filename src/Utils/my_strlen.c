/*
** my_strlen.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:58:55 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:58:56 2015 Hippolyte Barraud
*/

#include <42sh.h>

int	my_strlen(const char *str)
{
  int	i;

  if (!str)
    return (0);
  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int	is_empty(char *str)
{
  int	i;

  if (!str)
    return (1);
  i = 0;
  while (str[i] != '\0' && str[i] != '\n')
    {
      if (str[i] != ' ' && str[i] != '\t')
	return (0);
      i = i + 1;
    }
  return (1);
}
