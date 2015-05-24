/*
** xfork.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:59:27 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:59:28 2015 Hippolyte Barraud
*/

#include <42sh.h>

pid_t	xfork(void)
{
  pid_t	pid;

  if ((pid = fork()) == -1)
    {
      print_error(ERROR_FORK);
      return (-1);
    }
  return (pid);
}
