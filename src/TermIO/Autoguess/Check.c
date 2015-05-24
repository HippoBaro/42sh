/*
** check_autocomplete.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:55:00 2015 Hippolyte Barraud
** Last update Sat May 23 23:23:45 2015 Hippolyte Barraud
*/

#include <42sh.h>

char	*tabReturn(int *i, char *line, t_root *root)
{
  while (*i > 0 && (line[*i - 1] == ' '
		    || line[*i - 1] == '&' || line[*i - 1] == '|'
		    || line[*i - 1] == ';' || line[*i - 1] == '<'
		    || line[*i - 1] == '>'))
    if ((line = handleDeleteKey(i, line, root)) == NULL)
      return (NULL);
  while (*i > 0 && line[*i - 1] != ' '
	 && line[*i - 1] != '&' && line[*i - 1] != '|'
	 && line[*i - 1] != ';' && line[*i - 1] != '<'
	 && line[*i - 1] != '>')
    if ((line = handleDeleteKey(i, line, root)) == NULL)
      return (NULL);
  return (line);
}

int    	isInExes(char *line, t_exe *exes)
{
  t_exe	*current;

  current = exes->Next;
  while (current != NULL)
    {
      if (my_strcmp(current->Name, line) == 0)
	return (0);
      current = current->Next;
    }
  return (1);
}

int	isAlphanum(char totest)
{
  if ((totest >= 'a' && totest <= 'z') ||
      (totest >= 'A' && totest <= 'Z') || totest == '*' ||
      (totest >= '0' && totest <= '9') || totest == '-' ||
      totest == '_' || totest == '.' || totest == '/')
    return (1);
  return (0);
}

int	isFirstWord(char *line, int index)
{
  int	i;

  i = 0;
  while (line[i] != '\0' && line[i] != '\t' && isAlphanum(line[i]) == 1)
    i = i + 1;
  if (index <= i)
    return (1);
  return (0);
}

int		autoguessInFiles(char *line, int *ix, t_exe *exes, int isglob)
{
  glob_t	pglob;
  char		*tmp;
  int		i;
  int		ret;

  if ((tmp = getBin(line, ix, isglob)) == NULL)
    return (-1);
  ret = glob(tmp, GLOB_ERR | GLOB_TILDE | GLOB_MARK, NULL, &pglob);
  if (ret == GLOB_NOSPACE)
    return (print_error(ERROR_GLOB));
  if (ret == GLOB_NOMATCH || ret == GLOB_ABORTED)
    return (0);
  free(tmp);
  i = 0;
  while (i < (int)pglob.gl_pathc)
    {
      putExeInAutoguess(exes, pglob.gl_pathv[i]);
      i = i + 1;
    }
  return (0);
}
