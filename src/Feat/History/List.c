/*
** handle_history.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:50:03 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:50:03 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		hitoryListCount(t_history *history)
{
  t_history	*current;
  int		out;

  out = 0;
  current = history->Next;
  while (current != history)
    {
      out++;
      current = current->Next;
    }
  return (out);
}

char		*getHistoryNode(int index, t_history *history, int *flag)
{
  t_history	*current;
  int		i;
  char		*out;

  i = 0;
  current = history->Prev;
  while (current != history && current->Value != NULL && i < index)
    {
      i++;
      current = current->Prev;
    }
  if (current->Value == NULL)
    {
      *flag = 1;
      out = my_strdup(current->Next->Value);
      return (out);
    }
  *flag = 0;
  out = my_strdup(current->Value);
  return (out);
}

void		disposeHistoryNode(t_history *history)
{
  history->Prev->Next = history->Next;
  history->Next->Prev = history->Prev;
  if (history)
    free(history);
}

int		clearHistory(t_history *history, char flag)
{
  t_history	*current;

  if (flag == 1)
    current = history->Prev->Prev;
  else
    current = history->Prev;
  while (current != history)
    {
      if (current->Value == NULL || is_empty(current->Value) == 1)
	{
	  current = current->Prev;
	  disposeHistoryNode(current->Next);
	}
      current = current->Prev;
    }
  return (0);
}
