/*
** assign_function.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:52:14 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:22:51 2015 Hippolyte Barraud
*/

#include <42sh.h>

static const t_error	Errors[] = {
  {SIGQUIT, SIGNAL_SIGQUIT},
  {SIGILL, SIGNAL_SIGILL},
  {SIGABRT, SIGNAL_SIGABRT},
  {SIGFPE, SIGNAL_SIGFPE},
  {SIGSEGV, SIGNAL_SIGSEGV}
};

int	displayChildreenError(int error)
{
  int	i;

  i = 0;
  while (i < 5)
    {
      if (error == Errors[i].Value)
	print_error(Errors[i].Desc);
      i++;
    }
  return (-1);
}

static int	xwait(t_root *root)
{
  int		state;
  int		operator;
  t_pid		*current;

  resetFD(root->fd, 0);
  current = root->PID;
  waitpid(root->PID->PID, &state, 0);
  displayChildreenError(state);
  root->PID = root->PID->Next;
  free(current);
  while (root->PID)
    {
      current = root->PID;
      waitpid(root->PID->PID, &state, 0);
      root->PID = root->PID->Next;
      free(current);
    }
  if ((operator = checkOperator(root->Lexer2->Op)) == -1)
    return (-1);
  return (executeNextToken(root, state, operator));
}

static int	executionFailed(char *path)
{
  struct stat	info;

  print_error(path);
  if (lstat(path, &info) == -1)
    print_error(ERROR_EXEC_CMD_NOTFOUND);
  else
    if ((info.st_mode & S_IFDIR) != 0)
      print_error(ERROR_EXEC_ISDIR);
    else
      print_error(ERROR_CD_403);
  return (-1);
}

int    	executeCommand(t_root *token)
{
  char 	**paths;
  char 	**env;

  paths = getPaths(token->Env);
  if ((findCommand(paths, token->CmdArray) == -1) ||
      !(env = listToArray(token->Env)))
    return (-1);
  if (execve(token->CmdArray[0], token->CmdArray, env) == -1)
    return (executionFailed(token->CmdArray[0]));
  return (0);
}

int    	assignCommand(t_root *root)
{
  pid_t	pid;

  if ((pid = xfork()) == -1)
    return (-1);
  if (!(root->PID = addPidToList(root->PID, pid)))
    return (-2);
  if (pid == 0)
    {
      if (dup2(root->fd[0], 0) == -1 || dup2(root->fd[1], 1) == -1)
	{
	  print_error(ERROR_DUP2);
	  return (-2);
	}
      if (executeCommand(root) == -1)
	return (-2);
    }
  else
    return (xwait(root));
  return (0);
}
