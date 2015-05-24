/*
** handle_back_del.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:56:19 2015 Hippolyte Barraud
** Last update Sat May 23 23:27:08 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char	*deleteCharPrompt(char *line, int i)
{
  int		l;
  char		*tmp;

  if (my_strlen(&line[i - 1]) == 0)
    return (line);
  if ((tmp = xmalloc(sizeof(char) * (my_strlen(line) + 1))) == NULL)
    return (NULL);
  my_strcpy(tmp, line);
  if ((line = xmalloc(sizeof(char) * (my_strlen(tmp) + 2))) == NULL)
    return (NULL);
  my_strncpy(line, tmp, i);
  l = i - 1;
  while (tmp[i] != '\0')
    line[l++] = tmp[i++];
  line[l] = '\0';
  free(tmp);
  return (line);
}

char	*handleDeleteKey(int *i, char *line, t_root *root)
{
  (void)root;
  if (*i > 0)
    {
      my_putstr(tgetstr("le", NULL));
      my_putstr(tgetstr("dm", NULL));
      my_putstr(tgetstr("dc", NULL));
      if ((line = deleteCharPrompt(line, *i)) == NULL)
	return (NULL);
      *i -= 1;
      my_putstr(tgetstr("ed", NULL));
    }
  return (line);
}

char	*handleSuprKey(int *i, char *line, t_root *root)
{
  (void)root;
  my_putstr(tgetstr("dc", NULL));
  if ((line = deleteCharPrompt(line, *i + 1)) == NULL)
    return (NULL);
  return (line);
}
