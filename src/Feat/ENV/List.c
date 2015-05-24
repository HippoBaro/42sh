/*
** char_to_list.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:52:22 2015 Hippolyte Barraud
** Last update Sat May 23 23:07:56 2015 Hippolyte Barraud
*/

#include <42sh.h>

int	getArraySize(char **array)
{
  int	out;

  out = 0;
  while (array[out] != NULL)
    out = out + 1;
  return (out);
}

static int	keyLen(char *key)
{
  int		out;

  out = 0;
  while (key[out] && key[out] != '=')
    out = out + 1;
  return (out);
}

static int	fillNode(t_env *elem, char *value)
{
  int		i;
  int		j;

  if ((elem->Key = xmalloc(sizeof(char) * (keyLen(value) + 1))) == NULL)
    return (-1);
  if ((elem->Value = xmalloc(sizeof(char) *
			     (my_strlen(value) - keyLen(value)))) == NULL)
    return (-1);
  i = 0;
  while (value[i] != '\0' && value[i] != '=')
    {
      elem->Key[i] = value[i];
      i = i + 1;
    }
  elem->Key[i] = '\0';
  i = i + 1;
  j = 0;
  while (value[i] != '\0')
    elem->Value[j++] = value[i++];
  elem->Value[j] = '\0';
  return (0);
}

static int	addEnvNode(t_env *env, char *value)
{
  t_env		*node;

  if ((node = xmalloc(sizeof(*node))) == NULL)
    return (-1);
  if (fillNode(node, value) == -1)
    return (-1);
  node->Prev = env->Prev;
  node->Next = env;
  env->Prev->Next = node;
  env->Prev = node;
  return (0);
}

t_env		*arrayToList(char **array)
{
  t_env		*env;
  int		i;

  i = 0;
  if ((env = xcalloc(1, sizeof(*env))) == NULL)
    return (NULL);
  env->Next = env;
  env->Prev = env;
  env->Key = NULL;
  env->Value = NULL;
  while (array[i])
    {
      if (addEnvNode(env, array[i]) == -1)
	return (NULL);
      i++;
    }
  return (env);
}
