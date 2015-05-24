/*
** my_echo.c for miishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:51:10 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:51:11 2015 Hippolyte Barraud
*/

#include <42sh.h>

static void	echoString(char *str, int fd)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      if (str[i] != '\\')
	my_putchar_fd(str[i], fd);
      i++;
    }
}

static int	echoDashN(t_root *root)
{
  int		i;

  i = 2;
  while (root->CmdArray[i])
    {
      echoString(root->CmdArray[i], root->fd[1]);
      i++;
      if (root->CmdArray[i])
	my_putchar_fd(' ', root->fd[1]);
    }
  return (0);
}

int		echoFeat(t_root *root)
{
  int		i;

  i = 1;
  if (root->CmdArray[1] && my_strcmp(root->CmdArray[1], "-n") == 0)
    echoDashN(root);
  else
    {
      while (root->CmdArray[i])
	{
	  echoString(root->CmdArray[i], root->fd[1]);
	  i++;
	  if (root->CmdArray[i])
	    my_putchar_fd(' ', root->fd[1]);
	}
      my_putchar_fd('\n', root->fd[1]);
    }
  return (0);
}
