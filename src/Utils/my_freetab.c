/*
** my_freetab.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:57:39 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:57:40 2015 Hippolyte Barraud
*/

#include <42sh.h>

int	my_freetab(char **tab2)
{
  int	i;

  i = 0;
  if (!tab2)
    return (-1);
  while (tab2[i])
    {
      free(tab2[i]);
      i = i + 1;
    }
  return (0);
}
