/*
** my_setenv.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:49:42 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:19:04 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	putEnvNode(t_env *env, char *key, char *value)
{
  t_env		*node;

  if (!(node = xmalloc(sizeof(*node))))
    return (-1);
  if (!(node->Key = my_strdup(key)))
    return (-1);
  if (value && !(node->Value = my_strdup(value)))
    return (-1);
  if (!value)
    node->Value = my_strdup("");
  node->Prev = env->Prev;
  node->Next = env;
  env->Prev->Next = node;
  env->Prev = node;
  return (0);
}

int    	setEnv(t_env *env, char *key, char *value)
{
  t_env	*current;

  current = env->Next;
  while (current != env)
    {
      if (key && value && my_strcmp(key, current->Key) == 0)
	{
	  if (current->Value != NULL)
	    free(current->Value);
	  if ((current->Value = my_strdup(value)) == NULL)
	    return (-1);
	  return (0);
	}
      current = current->Next;
    }
  if (key && value)
    return (putEnvNode(env, key, value));
  return (-1);
}

int    	FeatEnv(t_root *root)
{
  t_env	*current;

  current = root->Env->Next;
  while (current != root->Env)
    {
      if (root->CmdArray[1] &&
	  my_strcmp(root->CmdArray[1], current->Key) == 0)
	{
	  free(current->Value);
	  if ((current->Value = my_strdup(root->CmdArray[2])) == NULL)
	    return (-1);
	  return (0);
	}
      current = current->Next;
    }
  if (root->CmdArray[1])
    return (putEnvNode(root->Env, root->CmdArray[1], root->CmdArray[2]));
  print_error(SETENV_USAGE);
  return (-1);
}
