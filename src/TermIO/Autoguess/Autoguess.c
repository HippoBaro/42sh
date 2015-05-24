/*
** autocomplete.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:54:45 2015 Hippolyte Barraud
** Last update Sat May 23 23:23:26 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char	*getNextBin(t_exe *exes)
{
  int		len;
  char		*out;
  int		i;

  len = getNewSize(exes);
  if ((out = xmalloc(sizeof(char) * (len + 1))) == NULL)
    return (NULL);
  i = 0;
  while (i < len)
    {
      out[i] = exes->Next->Name[i];
      i++;
    }
  out[i] = '\0';
  return (out);
}

static char	*autoguessReplace(char *line, t_exe *exex,
				  int *i, t_root *root)
{
  char		*current;

  if ((current = getNextBin(exex)) != NULL)
    {
      if (*i != 0 && isAlphanum(line[*i - 1]) == 1)
	line = tabReturn(i, line, root);
      line = putStringInPrompt(line, *i, current);
      free(current);
    }
  return (line);
}

static void   	replaceIndex(char *line, t_root *root, t_exe *exes, int *i)
{
  *i = my_strlen(line);
  displayPrompt(root);
  my_putstr(line);
  disposeLastExes(exes);
}

char		*autoguess(int *i, char *line, t_root *root)
{
  int		isGlob;
  t_exe		*exes;
  int		lenght;

  if (isatty(0) == 0)
    return (line);
  isGlob = lineHasGlob(&line[*i]);
  if (!(exes = xmalloc(sizeof(*exes))))
    return (line);
  exes->Next = NULL;
  if (isFirstWord(line, *i) == 1 && line[0] != '.')
    {
      if (autoguessExes(root, line, exes) == -1)
	return (line);
    }
  else if (autoguessInFiles(line, i, exes, isGlob) == -1)
    return (line);
  lenght = exesLenght(exes);
  checkAutoguessLenght(exes, lenght);
  while (line[*i] != '\0' && line[*i] != ' ' && line[*i] != '\t')
    *i = *i + 1;
  if ((lenght > 0 && isGlob == 0) || lenght == 1)
    line = autoguessReplace(line, exes, i, root);
  replaceIndex(line, root, exes, i);
  return (line);
}

char   	*getBin(char *line, int *i, int isglob)
{
  char 	*current;
  int  	l;
  int  	k;

  l = 0;
  while (*i >= 0 && (line[*i] == ' ' || line[*i] == '\t'))
    *i -= 1;
  while (*i - l >= 0 && line[*i - l] != ' ' && line[*i - l] != '\t')
    l++;
  l--;
  if ((current = xmalloc(sizeof(char) * (l + 3 - isglob))) == NULL)
    return (NULL);
  k = 0;
  while (*i - l <= *i && line[*i - l] != '\0' &&
	 line[*i - l] != ' ' && line[*i - l] != '\t')
    current[k++] = line[*i - l--];
  if (isglob == 0)
    {
      current[k] = '*';
      current[k + 1] = '\0';
    }
  else
    current[k] = '\0';
  return (current);
}
