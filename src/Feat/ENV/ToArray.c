/*
** list_to_char.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:53:29 2015 Hippolyte Barraud
** Last update Sat May 23 23:08:38 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	countEnvNode(t_env *env)
{
  t_env		*current;
  int		i;

  i = 0;
  current = env->Next;
  while (current != env)
    {
      current = current->Next;
      i = i + 1;
    }
  return (i);
}

static char	*putInArray(t_env *node)
{
  char		*out;
  int		i;
  int		j;

  j = 0;
  i = 0;
  out = xmalloc(sizeof(char) * (my_strlen(node->Key)
				+ my_strlen(node->Value) + 2));
  while (node->Key[i] != '\0')
    out[j++] = node->Key[i++];
  out[j++] = '=';
  i = 0;
  while (node->Value[i] != '\0')
    out[j++] = node->Value[i++];
  out[j] = '\0';
  return (out);
}

char		**listToArray(t_env *env)
{
  t_env		*current;
  char		**out;
  int		i;

  i = 0;
  out = xmalloc(sizeof(char *) * (countEnvNode(env) + 1));
  current = env->Next;
  while (current != env)
    {
      if ((out[i++] = putInArray(current)) == NULL)
	return (NULL);
      current = current->Next;
    }
  out[i] = NULL;
  return (out);
}
