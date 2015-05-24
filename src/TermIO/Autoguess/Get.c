/*
** autocomplete_binaries.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:54:53 2015 Hippolyte Barraud
** Last update Sat May 23 23:24:50 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char	*getExeName(char *line)
{
  int		i;
  int		j;
  char		*name;

  i = 0;
  while (line[i])
    i = i + 1;
  while (line[i] != '/' && i > 0)
    i = i - 1;
  if (!(name = xmalloc(sizeof(char) * (my_strlen(line) - i))))
    return (NULL);
  i = i + 1;
  j = 0;
  while (line[i])
    name[j++] = line[i++];
  name[j] = '\0';
  return (name);
}

static char	*getPath(char *path, char *line)
{
  char		*out;

  if (!(out = realloc(path, sizeof(char) * (my_strlen(path)
					    + my_strlen(line) + 3))))
    return (NULL);
  out = my_strcat(out, "/");
  out = my_strcat(out, line);
  out = my_strcat(out, "*");
  return (out);
}

static int	get_in_path(char *ph, t_exe *exes, char *line)
{
  glob_t	glopreturn;
  int		index;
  char		*current;
  int		result;

  if (!(ph = getPath(ph, line)))
    return (-1);
  result = glob(ph, GLOB_ERR | GLOB_TILDE | GLOB_MARK, NULL, &glopreturn);
  if (result == GLOB_NOSPACE)
    return (print_error(ERROR_GLOB));
  if (result == GLOB_NOMATCH || result == GLOB_ABORTED)
    return (0);
  index = 0;
  while (index < (int)glopreturn.gl_pathc)
    {
      if (!(current = getExeName(glopreturn.gl_pathv[index])))
	return (-1);
      if (isInExes(current, exes) == 1)
	putExeInAutoguess(exes, current);
      free(current);
      index = index + 1;
    }
  return (0);
}

static char	*getLine(char *line)
{
  char		*out;
  int		index;

  index = 0;
  while (line[index] != '\0' && line[index] != '\t'
	 && isAlphanum(line[index]) == 1)
    index++;
  if (!(out = xmalloc(sizeof(char) * (index + 1))))
    return (NULL);
  index = 0;
  while (line[index] != '\0' && line[index] != '\t'
	 && isAlphanum(line[index]) == 1)
    {
      out[index] = line[index];
      index++;
    }
  out[index] = '\0';
  return (out);
}

int	autoguessExes(t_root *root, char *line, t_exe *exes)
{
  char	**paths;
  char	*pwd;
  int	i;
  char	*path;

  if (!(path = getLine(line)))
    return (-1);
  i = 0;
  if ((pwd = getEnv("PATH", root->Env)) == NULL)
    return (print_error(ERROR_EXEC_CMD_NOTFOUND "\n" ERROR_SETENV_CANTGET));
  if ((paths = pathToArray(pwd)) == NULL)
    return (-1);
  while (paths[i])
    if (get_in_path(paths[i++], exes, path) == -1)
      return (-1);
  free(path);
  sortExes(exes);
  return (0);
}
