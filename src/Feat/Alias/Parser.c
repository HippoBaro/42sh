/*
** parse_alias.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:49:00 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:49:01 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	wordCount(char *cmd)
{
  int		out;
  int		i;
  char		sep;

  i = 0;
  out = 0;
  while (cmd[i] != '\0')
    {
      if (cmd[i] == ' ' || cmd[i] == '\n' || cmd[i] == '"' || cmd[i] == 39)
	i++;
      else
	{
	  out++;
	  if (i > 0 && (cmd[i - 1] == '"' || cmd[i - 1] == 39))
	    {
	      sep = cmd[i - 1];
	      while (cmd[i] != '\n' && cmd[i] != sep && cmd[i] != '\0')
		i++;
	    }
	  else
	    while (cmd[i] != '\n' && cmd[i] != ' ' && cmd[i] != '\0')
	      i++;
	}
    }
  return (out);
}

static int	wordLen(char *str, int i)
{
  int		j;
  char		sep;

  j = 1;
  i++;
  if (i > 1 && (str[i - 1] != '"' || str[i - 1] != 39))
    {
      sep = str[i - 2];
      while (str[i] != sep && str[i] != '\0' && str[i] != '\n')
	{
	  i++;
	  j++;
	}
    }
  else
    while (str[i] != ' ' && str[i] != '\0' && str[i] != '\n')
      {
	i++;
	j++;
      }
  return (j + 1);
}

static void	putNuminArray(int *y, int *i, char *str, char **out)
{
  int		z;

  z = 0;
  out[*y][z] = str[*i];
  *i = *i + 1;
  z++;
  while (str[*i] != ' ' && str[*i] != '\0' && str[*i] != '\n')
    {
      out[*y][z] = str[*i];
      *i = *i + 1;
      z++;
    }
  out[*y][z] = '\0';
  *y = *y + 1;
}

static void	putQuoteinArray(int *y, int *i, char *str, char **out)
{
  int		z;
  char		sep;

  z = 0;
  out[*y][z] = str[*i];
  *i = *i + 1;
  z++;
  sep = str[(*i) - 2];
  while (str[*i] != sep && str[*i] != '\0' && str[*i] != '\n')
    {
      out[*y][z] = str[*i];
      *i = *i + 1;
      z++;
    }
  out[*y][z] = '\0';
  *y = *y + 1;
}

char	**parseAlias(char *cmd)
{
  int	i;
  int	y;
  char	**out;

  out = xmalloc(sizeof(char *) * (wordCount(cmd) + 1));
  if (out == NULL)
    return (NULL);
  y = 0;
  i = 0;
  while (cmd[i] != '\0')
    {
      if (cmd[i] == ' ' || cmd[i] == '\n' || cmd[i] == '"' || cmd[i] == 39)
	i++;
      else
	{
	  if ((out[y] = xmalloc(sizeof(char) * wordLen(cmd, i))) == NULL)
	    return (NULL);
	  if (i > 0 && (cmd[i - 1] == '"' || cmd[i - 1] == 39))
	    putQuoteinArray(&y, &i, cmd, out);
	  else
	    putNuminArray(&y, &i, cmd, out);
	}
    }
  out[y] = '\0';
  return (out);
}
