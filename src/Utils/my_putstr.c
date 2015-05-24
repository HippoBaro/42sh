/*
** my_putstr.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:58:15 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:58:17 2015 Hippolyte Barraud
*/

#include <42sh.h>

void	my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

void	my_putstr_fd(char *str, int fd)
{
  write(fd, str, my_strlen(str));
}

int	print_error(char *str)
{
  write(2, RED, 5);
  write(2, str, my_strlen(str));
  write(2, BLANK, 4);
  return (-1);
}
