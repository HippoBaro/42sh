/*
** my_alias.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:48:17 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:48:18 2015 Hippolyte Barraud
*/

#include <42sh.h>

static t_alias	*initAlias()
{
  t_alias	*out;

  out = xcalloc(1, sizeof(*out));
  if (out == NULL)
    return (NULL);
  out->Prev = out;
  out->Name = NULL;
  out->Args = NULL;
  out->Next = out;
  return (out);
}

int		setAlias(t_alias *alias, char *name, char *value)
{
  t_alias	*new;
  char		**tab2;

  if (!(tab2 = parseAlias(value)))
    return (-1);
  new = xmalloc(sizeof(*new));
  if (new == NULL)
    return (-1);
  new->Name = name;
  new->Args = tab2;
  new->Prev = alias;
  new->Next = alias->Next;
  alias->Next->Prev = new;
  alias->Next = new;
  return (0);
}

static int	getAliasLine(int fd, t_alias *alias)
{
  char		*line;
  char		*name;
  char		*value;

  while ((line = get_next_line(fd)) != NULL)
    {
      if (is_empty(line) == 0)
	{
	  if (!(name = getAliasKey(line)))
	    return (-1);
	  if (!(value = getAliasValue(line)))
	    return (-1);
	  if (setAlias(alias, name, value) == -1)
	    return (-1);
	}
      else
      	free(line);
    }
  return (0);
}

t_alias		*getAliases(t_env *env)
{
  t_alias	*alias;
  int		fd;
  char		*file;

  if ((alias = initAlias()) == NULL)
    return (NULL);
  file = getAliasFile(env);
  if (file == NULL)
    return (alias);
  fd = open(file, O_RDONLY);
  free(file);
  if (fd <= 0)
    return (alias);
  if (getAliasLine(fd, alias) == -1)
    return (alias);
  close (fd);
  return (alias);
}
