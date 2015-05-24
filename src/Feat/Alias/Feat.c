/*
** my_alias_built_in.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:48:25 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:48:26 2015 Hippolyte Barraud
*/

#include <42sh.h>

static void	displayAlias(t_alias *alias)
{
  t_alias	*current;
  int		i;

  current = alias->Prev;
  while (current != alias)
    {
      i = 0;
      my_putstr(BLUE "alias " BLANK);
      my_putstr(current->Name);
      my_putchar('=');
      while (current->Args && current->Args[i])
	{
	  my_putstr(current->Args[i]);
	  i = i + 1;
	  if (current->Args[i])
	    my_putchar(' ');
	}
      current = current->Prev;
      my_putchar('\n');
    }
}

static int	replaceAlias(t_alias *alias, char *value)
{
  char		**array;

  if (!(array = parseAlias(value)))
    return (-1);
  my_freetab(alias->Args);
  free(alias->Args);
  alias->Args = array;
  return (0);
}

static void	writeAliasOnFile(t_alias *alias, int fd)
{
  int		i;

  i = 0;
  write(fd, alias->Name, my_strlen(alias->Name));
  write(fd, "=", 1);
  while (alias->Args && alias->Args[i])
    {
      write(fd, alias->Args[i], my_strlen(alias->Args[i]));
      i = i + 1;
      if (alias->Args[i])
	write(fd, " ", 1);
    }
  write(fd, "\n", 1);
}

static int	saveAlias(t_alias *alias, t_env *env)
{
  t_alias	*tmp;
  int		fd;
  char		*file;

  tmp = alias->Prev;
  if ((file = getAliasFile(env)) == NULL)
    return (-1);
  if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (print_error(ERROR_OPEN_CONFIG_FILE));
  free(file);
  while (tmp != alias)
    {
      writeAliasOnFile(tmp, fd);
      tmp = tmp->Prev;
    }
  close(fd);
  return (0);
}

int		alias(t_root *root)
{
  t_alias	*current;
  char		*name;

  if (root->CmdArray[1] == NULL)
    displayAlias(root->Aliases);
  else if (root->CmdArray[1] && root->CmdArray[2])
    {
      current = root->Aliases->Next;
      while (current != root->Aliases)
	{
	  if (my_strcmp(current->Name, root->CmdArray[1]) == 0)
	    return (replaceAlias(current, root->CmdArray[2]));
	  current = current->Next;
	}
      if (!(name = my_strdup(root->CmdArray[1])))
	return (-1);
      setAlias(root->Aliases, name, root->CmdArray[2]);
    }
  else
    return (print_error(ALIAS_USAGE));
  if (saveAlias(root->Aliases, root->Env) == -1)
    return (-1);
  return (0);
}
