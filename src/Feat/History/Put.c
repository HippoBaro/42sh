/*
** put_in_hist.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:56:59 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:57:00 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		putNodeInHistorySecure(t_history *history, char *data)
{
  t_history	*new;

  if (my_strcmp(history->Prev->Value, data) == 0)
    return (0);
  new = xmalloc(sizeof(*new));
  new->Value = xmalloc(sizeof(char) * (my_strlen(data) + 1));
  if (new->Value == NULL)
    return (-1);
  new->Index = 0;
  new->Value = historyCpy(new->Value, data);
  new->Next = history;
  new->Prev = history->Prev;
  history->Prev->Next = new;
  history->Prev = new;
  return (0);
}

int		putNodeInHistory(t_history *history, char *data)
{
  t_history	*new;

  new = xmalloc(sizeof(*new));
  new->Value = xmalloc(sizeof(char) * (my_strlen(data) + 1));
  if (new->Value == NULL)
    return (-1);
  new->Value = historyCpy(new->Value, data);
  new->Index = 0;
  new->Prev = history;
  new->Next = history->Next;
  history->Next->Prev = new;
  history->Next = new;
  return (0);
}
