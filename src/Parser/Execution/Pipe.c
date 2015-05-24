/*
** exec_in_pipe.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:52:04 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:31:08 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	executeWithPipe(t_root *root)
{
  pid_t		pid;

  if ((pid = xfork()) == -1)
    return (-1);
  if (!(root->PID = addPidToList(root->PID, pid)))
    return (-2);
  if (pid == 0)
    {
      setsid();
      resetFD(root->fd, 0);
      if (root->fd[2] != 0)
	root->fd[0] = root->fd[2];
      if (dup2(root->fd[0], 0) == -1 || dup2(root->fd[1], 1) == -1)
	{
	  print_error(ERROR_DUP2);
	  return (-2);
	}
      if (checkFeats(root) == -2 && executeCommand(root) == -1)
	return (-2);
      return (-2);
    }
  return (0);
}

static int	setFD(t_root *root)
{
  int		old;

  old = 0;
  if (root->fd[0] != 0)
    root->fd[2] = root->fd[0];
  if (root->fd[1] != 1)
    old = root->fd[1];
  if (pipe(root->fd) == -1)
    {
      root->Lexer2 = root->Lexer2->Next;
      return (print_error(ERROR_PIPE));
    }
  return (old);
}

int    	handlePipe(t_root *root)
{
  int  	old;

  if ((old = setFD(root)) == -1)
    return (-1);
  if (old != 0)
    {
      if (close(root->fd[1]) == -1)
	print_error(ERROR_CLOSE);
      root->fd[1] = old;
    }
  if (executeWithPipe(root) == -2)
    return (-2);
  if (root->fd[2] != 0 && close(root->fd[2]) == -1)
    print_error(ERROR_CLOSE);
  root->fd[2] = 0;
  resetFD(root->fd, 1);
  root->Lexer2 = root->Lexer2->Next;
  return (0);
}
