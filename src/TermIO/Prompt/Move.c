/*
** handle_directions.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 02:01:15 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:33:49 2015 Hippolyte Barraud
*/

#include <42sh.h>

char	*handleLeftKey(int *i, char *line, t_root *root)
{
  (void)root;
  if (*i > 0)
    {
      *i -= 1;
      my_putstr(tgetstr("le", NULL));
    }
  return (line);
}

char	*handleRightKey(int *i, char *line, t_root *root)
{
  (void)root;
  if (*i < my_strlen(line))
    {
      *i += 1;
      my_putstr(tgetstr("nd", NULL));
    }
  return (line);
}

char	*handleHistoryDownKey(t_root *root, int *i, int *histIndex, char *line)
{
  int	last;

  if (*histIndex > 0)
    {
      while (*i < my_strlen(line))
	{
	  *i += 1;
	  my_putstr(tgetstr("nd", NULL));
	}
      while (*i > 0)
	handleDeleteKey(i, line, root);
      line = getHistoryNode(*histIndex - 1, root->History, &last);
      my_putstr(line);
      *i = my_strlen(line);
      if (last == 0)
	*histIndex -= 1;
    }
  return (line);
}

char	*handleHistoryUpKey(t_root *root, int *i, int *histIndex, char *line)
{
  int	first;

  clearHistory(root->History, 1);
  if (*histIndex == 0)
    putNodeInHistorySecure(root->History, line);
  if (*histIndex < HISTORY_MAX && *histIndex < hitoryListCount(root->History))
    {
      while (*i < my_strlen(line))
	{
	  *i += 1;
	  my_putstr(tgetstr("nd", NULL));
	}
      while (*i > 0)
	handleDeleteKey(i, line, root);
      line = getHistoryNode(*histIndex + 1, root->History, &first);
      my_putstr(line);
      *i = my_strlen(line);
      if (first == 0)
	*histIndex += 1;
    }
  return (line);
}
