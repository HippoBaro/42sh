/*
** init.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:53:21 2015 Hippolyte Barraud
** Last update Sat May 23 23:13:30 2015 Hippolyte Barraud
*/

#include <42sh.h>

void	resetFD(int *fd, int index)
{
  if (fd[index] != index && close(fd[index]) == -1)
    print_error(ERROR_CLOSE);
  fd[index] = index;
}

static void    	signalHandler(int id, t_root *root)
{
  static t_root	*old = NULL;

  if (!old)
    old = root;
  if (id == SIGINT)
    {
      my_putchar('\n');
      if (!old->Backgrounded && old->PID == NULL)
	displayPrompt(old);
      else if (!old->Backgrounded)
	kill(old->PID->PID, id);
    }
}

t_lexer		*getNewParser(void)
{
  t_lexer	*out;

  if (!(out = xmalloc(sizeof(*out))))
    return (NULL);
  out->init = FALSE;
  out->Prev = out;
  out->Next = out;
  return (out);
}

static void		lifeIsHard(int id)
{
  if (id == SIGSEGV)
    {
      print_error(ERROR_FATAL);
      kill(this, SIGTERM);
    }
}

t_root		*getNewRoot(int ac, char **av, char **ep)
{
  t_root       	*out;

  (void)ac;
  (void)av;
  if (!(out = xmalloc(sizeof(*out))))
    return (NULL);
  out->fd[0] = 0;
  out->fd[1] = 1;
  out->fd[2] = 0;
  out->IndexLex = 1;
  out->PID = NULL;
  if (!(out->Env = arrayToList(ep)))
    return (NULL);
  signalHandler(0, out);
  if (signal(SIGTSTP, (void (*)(int))signalHandler) == SIG_ERR)
    print_error(ERROR_SIGNAL);
  if (signal(SIGINT, (void (*)(int))signalHandler) == SIG_ERR)
    print_error(ERROR_SIGNAL);
  if (signal(SIGSEGV, lifeIsHard) == SIG_ERR)
    print_error(ERROR_SIGNAL);
  return (out);
}
