/*
** prompt.c for 42sh in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Mon May 11 21:07:49 2015 Hippolyte Barraud
** Last update Sat May 23 23:29:10 2015 Hippolyte Barraud
*/

#include <42sh.h>

char	*clearTerminal(int *i, char *line, t_root *root)
{
  (void)i;
  my_putstr(tgetstr("cl", NULL));
  displayPrompt(root);
  return (line);
}

char		*printHistory(int *i, char *line, t_root *root)
{
  t_history	*current;
  int		l;

  (void)i;
  l = 0;
  current = root->History->Next;
  my_putchar_fd('\n', root->fd[1]);
  while (current != root->History)
    {
      my_put_nbr_fd(++l, root->fd[1]);
      my_putchar_fd('\t', root->fd[1]);
      my_putstr_fd(current->Value, root->fd[1]);
      my_putchar_fd('\n', root->fd[1]);
      current = current->Next;
    }
  displayPrompt(root);
  return (line);
}
