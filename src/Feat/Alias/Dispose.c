/*
** my_unalias.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:48:45 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:48:46 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		unalias(t_root *root)
{
  t_alias	*current;

  current = root->Aliases->Next;
  while (current != root->Aliases)
    {
      if (my_strcmp(current->Name, root->CmdArray[1]) == 0)
	{
	  current->Prev->Next = current->Next;
	  current->Next->Prev = current->Prev;
	  free(current);
	  return (0);
	}
      current = current->Next;
    }
  return (print_error(ERROR_ALIAS_404));
}
