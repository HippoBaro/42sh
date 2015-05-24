/*
** my_putchar.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:57:55 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:57:56 2015 Hippolyte Barraud
*/

#include <42sh.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putchar_fd(char c, int fd)
{
  write(fd, &c, 1);
}
