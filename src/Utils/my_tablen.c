/*
** my_tablen.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:59:13 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:59:14 2015 Hippolyte Barraud
*/

#include <42sh.h>

int	my_tablen(char **tab2)
{
  int	i;

  i = 0;
  while (tab2[i])
    i++;
  return (i);
}
