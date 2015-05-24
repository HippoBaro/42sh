/*
** my_env.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:49:20 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:49:21 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		envFeat(t_root *root)
{
  t_env		*current;

  current = root->Env->Next;
  while (current != root->Env)
    {
      my_putstr_fd(current->Key, root->fd[1]);
      my_putchar_fd('=', root->fd[1]);
      my_putstr_fd(current->Value, root->fd[1]);
      my_putchar_fd('\n', root->fd[1]);
      current = current->Next;
    }
  return (0);
}

int    	unSetEnv(t_root *root)
{
  t_env	*current;

  current = root->Env->Next;
  while (current != root->Env)
    {
      if (my_strcmp(root->CmdArray[1], current->Key) == 0)
	{
	  current->Prev->Next = current->Next;
	  current->Next->Prev = current->Prev;
	  free(current);
	  return (0);
	}
      current = current->Next;
    }
  if (root->CmdArray[1])
    {
      print_error(root->CmdArray[1]);
      print_error(ERROR_UNSETENV_404);
    }
  else
    print_error(UNSETENV_USAGE);
  return (-1);
}

char   	*getEnv(char *key, t_env *env)
{
  t_env	*current;

  current = env->Next;
  while (key && current != env)
    {
      if (my_strcmp(current->Key, key) == 0)
	return (current->Value);
      current = current->Next;
    }
  return (NULL);
}
