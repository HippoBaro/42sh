/*
** get_path.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:52:54 2015 Hippolyte Barraud
** Last update Sat May 23 23:20:11 2015 Hippolyte Barraud
*/

#include <42sh.h>

int    	commandNotFound(char *path, char **paths, char **cmdarray)
{
  print_error(cmdarray[0]);
  print_error(ERROR_EXEC_CMD_NOTFOUND);
  free(path);
  my_freetab(paths);
  free(paths);
  return (-1);
}

char   	**getPaths(t_env *env)
{
  char 	*path;
  char 	**out;

  if (!(path = getEnv("PATH", env)))
    return (NULL);
  if (!(out = pathToArray(path)))
    {
      print_error(ERROR_GET_PATH);
      return (NULL);
    }
  return (out);
}

static char	*getCommandPath(char *dir, char *name)
{
  char		*path;
  int		i;
  int		k;

  if (!name)
    return (NULL);
  path = xmalloc((my_strlen(dir) + my_strlen(name) + 2) * sizeof(*path));
  if (!path)
    return (NULL);
  i = -1;
  while (dir[++i] != '\0')
    path[i] = dir[i];
  path[i++] = '/';
  k = 0;
  while (name[k] != '\0')
    path[i++] = name[k++];
  path[i] = '\0';
  return (path);
}

static char   	*checkPath(char **paths, char **cmdarray)
{
  int		i;
  char		*out;

  if (!paths)
    return (cmdarray[0]);
  i = 0;
  if (!(out = getCommandPath(paths[i], cmdarray[0])))
    return (NULL);
  while (access(out, X_OK) == -1 && paths[++i])
    {
      free(out);
      if (!(out = getCommandPath(paths[i], cmdarray[0])))
	return (NULL);
    }
  if (!paths[i] && commandNotFound(out, paths, cmdarray) == -1)
    return (NULL);
  free(cmdarray[0]);
  return (out);
}

int    	findCommand(char **paths, char **cmdarray)
{
  if (!(cmdarray && (cmdarray[0][0] == '/' ||
		     !my_strncmp(cmdarray[0], "./", 2))) &&
      !(cmdarray[0] = checkPath(paths, cmdarray)))
    return (-1);
  if (paths)
    {
      my_freetab(paths);
      free(paths);
    }
  return (0);
}
