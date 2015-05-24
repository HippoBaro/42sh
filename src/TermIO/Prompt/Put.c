/*
** put_del_str.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:56:46 2015 Hippolyte Barraud
** Last update Sat May 23 23:28:52 2015 Hippolyte Barraud
*/

#include <42sh.h>

char		*putStringInPrompt(char *line, int i, char *toadd)
{
  int		l;
  char		*current;
  int		y;

  if ((current = xmalloc(sizeof(char) * (my_strlen(line) + 1))) == NULL)
    return (NULL);
  my_strcpy(current, line);
  if ((line = xmalloc(sizeof(char) * (my_strlen(current)
				      + my_strlen(toadd) + 1))) == NULL)
    return (NULL);
  my_strncpy(line, current, i);
  y = 0;
  l = i;
  while (toadd[y] != '\0')
    line[l++] = toadd[y++];
  while (current[i] != '\0')
    {
      line[l] = current[i];
      l++;
      i++;
    }
  line[l] = '\0';
  free(current);
  return (line);
}

int		putExeInAutoguess(t_exe *exes, char *name)
{
  t_exe		*list;
  t_exe		*current;

  current = exes;
  list = xmalloc(sizeof(*list));
  if (list == NULL)
    return (-1);
  list->Name = xmalloc(sizeof(char) * (my_strlen(name) + 1));
  if (list->Name == NULL)
    return (-1);
  my_strcpy(list->Name, name);
  list->Next = NULL;
  while (current->Next != NULL)
    current = current->Next;
  current->Next = list;
  return (0);
}
