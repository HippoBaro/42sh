/*
** sort_bin.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:55:26 2015 Hippolyte Barraud
** Last update Sat May 23 23:26:43 2015 Hippolyte Barraud
*/

#include <42sh.h>

static void	putNodeAtSortedPlace(t_exe *next, t_exe *current,
				     t_exe *out, char *name)
{
  while (next->Next != NULL &&
	 my_strcmp(next->Name, name) < 0)
    {
      current = current->Next;
      next = current->Next;
    }
  if (my_strcmp(next->Name, name) < 0)
    next->Next = out;
  else
    {
      current->Next = out;
      out->Next = next;
    }
}

static t_exe	*putNode(t_exe *exes, char *name)
{
  t_exe		*current;
  t_exe		*out;
  t_exe		*next;

  if ((out = xmalloc(sizeof(t_exe))) == NULL)
    return (NULL);
  out->Name = name;
  out->Next = NULL;
  if (exes == NULL)
    return out;
  current = exes;
  next = current->Next;
  if (my_strcmp(current->Name, name) < 0)
    {
      if (next == NULL)
	current->Next = out;
      else
	putNodeAtSortedPlace(next, current, out, name);
      return (current);
    }
  else
    out->Next = current;
  return (out);
}

int		sortExes(t_exe *exes)
{
  t_exe		*current;
  t_exe		*out;

  out = NULL;
  current = exes->Next;
  while (current != NULL)
    {
      out = putNode(out, current->Name);
      current = current->Next;
    }
  if (out == NULL)
    return (-1);
  disposeExes(exes);
  exes->Next = out;
  return (0);
}
