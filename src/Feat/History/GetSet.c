/*
** history.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:50:10 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:20:30 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		saveHistory(t_history *history, t_env *env)
{
  t_history	*current;
  int		fd;
  int		i;
  char		*file;

  i = 0;
  current = history->Prev;
  if ((file = getHistoryFile(env)) == NULL)
    return (-1);
  if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (print_error(ERROR_OPEN_HISTORY_FILE));
  free(file);
  while (current != history && i < HISTORY_MAX)
    {
      if (is_empty(current->Value) == 0)
	{
	  write(fd, current->Value, my_strlen(current->Value));
	  write(fd, "\n", 1);
	}
      current = current->Prev;
      i = i + 1;
    }
  close (fd);
  return (0);
}

t_history      	*initHistory(void)
{
  t_history	*out;

  out = xcalloc(1, sizeof(*out));
  out->Prev = out;
  out->Value = NULL;
  out->Next = out;
  return (out);
}

static int	getHistoryLine(int fd, t_history *history)
{
  char		*str;

  while ((str = get_next_line(fd)) != NULL)
    {
      if (is_empty(str) == 0)
	{
	  if (putNodeInHistory(history, str) == -1)
	    return (-1);
	}
      else
      	free(str);
    }
  return (0);
}

t_history      	*getHistory(t_env *env)
{
  t_history	*out;
  int		fd;
  char		*file;

  if ((out = initHistory()) == NULL)
    return (NULL);
  file = getHistoryFile(env);
  if (file == NULL)
    return (out);
  fd = open(file, O_RDONLY);
  free(file);
  if (fd <= 0)
    return (out);
  if (getHistoryLine(fd, out) == -1)
    return (NULL);
  close (fd);
  return (out);
}

char   	*getHistoryFile(t_env *env)
{
  char 	*out;
  char 	*homedir;

  homedir = getEnv("HOME", env);
  if (homedir == NULL)
    return (NULL);
  if (!(out = xmalloc(sizeof(char) * (my_strlen(HISTORY_FILE_NAME)
				       + my_strlen(homedir) + 1))))
    return (NULL);
  my_strcpy(out, homedir);
  out = my_strcat(out, HISTORY_FILE_NAME);
  return (out);
}
