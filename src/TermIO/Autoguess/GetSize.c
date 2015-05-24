/*
** get_autocomplete_size.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:55:10 2015 Hippolyte Barraud
** Last update Sat May 23 23:25:43 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		getLittleLenght(t_exe *exes)
{
  int		index;
  int		out;
  t_exe		*current;

  current = exes->Next;
  index = 0;
  out = my_strlen(current->Name);
  while (current != NULL)
    {
      if (my_strlen(current->Name) < out)
	out = my_strlen(current->Name);
      index++;
      current = current->Next;
    }
  return (out);
}

int		getNewSize(t_exe *bin)
{
  int		out;
  int		littleLenght;
  t_exe		*current;

  out = 0;
  littleLenght = getLittleLenght(bin);
  while (out < littleLenght)
    {
      current = bin->Next;
      while (current != NULL && current->Next != NULL)
	{
	  if (current->Name[out] != current->Next->Name[out])
	    return (out);
	  current = current->Next;
	}
      out++;
    }
  return (out);
}
