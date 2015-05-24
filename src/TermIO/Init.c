/*
** init_fcts.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:56:38 2015 Hippolyte Barraud
** Last update Sat May 23 23:22:54 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int		initTermIO(void)
{
  struct termios	termIO;

  if (tcgetattr(0, &termIO) == -1)
    return (-1);
  termIO.c_lflag &= ~ICANON;
  termIO.c_lflag &= ~ECHO;
  if (tcsetattr(0, 0, &termIO) == -1)
    return (-1);
  return (0);
}

char		*initTermLine(int *i)
{
  char		*out;

  if ((out = xmalloc(sizeof(*out) * 1)) == NULL)
    return (NULL);
  out[0] = '\0';
  *i = 0;
  if (initTermIO() == -1)
    return (NULL);
  return (out);
}
