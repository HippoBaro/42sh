/*
** parser.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:54:18 2015 Hippolyte Barraud
** Last update Sat May 23 23:35:29 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char	*getTokenQuotesAt(char *line, int *i)
{
  int		l;
  char		quote;
  char		*out;

  quote = line[*i];
  l = ++(*i);
  while (line[l] && line[l] != quote)
    l++;
  if (!(out = xmalloc(sizeof(*out) * (l + 1))))
    return (NULL);
  l = 0;
  while (line[*i] && line[(*i)] != quote)
    out[l++] = line[(*i)++];
  out[l] = '\0';
  if (line[*i] != '\0')
    (*i)++;
  return (out);
}

static char	*getTokenAt(char *line, int *i, int *first)
{
  int		l;
  char		*out;

  if (line[*i] == '\'' || line[*i] == '"')
    return (getTokenQuotesAt(line, i));
  if (!(out = xmalloc(sizeof(*out) * (getTokenLenght(&line[*i]) + 1))))
    return (NULL);
  l = 0;
  while (line[*i] && !IS_SEP(line[*i]))
    {
      if (*first == 0 && line[*i] == '<')
	{
	  unexpectedOperator("<");
	  return (NULL);
	}
      *first = 1;
      out[l++] = line[(*i)++];
    }
  out[l] = '\0';
  if (line[*i] != '\0')
    (*i)++;
  return (out);
}

static char	**getToken(char *line, char **array, t_lexer *parser, int *l)
{
  char 	op;

  if (!line[0])
    {
      free(line);
      return (array);
    }
  if ((op = checkOperator(line)) != -1)
    {
      if (addTokenToList(parser, array, line) == -1)
	return (NULL);
      *l = 0;
    }
  else
    {
      if (!(array = realloc(array, (*l + 2) * sizeof(*array))))
	return (NULL);
      array[(*l)++] = line;
      array[*l] = NULL;
    }
  return (array);
}

static int	putEndCommand(char *line, char **array, t_lexer *parser, int l)
{
  char 	*operator;

  if (line && !line[0])
    {
      free(line);
      free(array);
      free(parser);
      return (-1);
    }
  free(line);
  if (!(operator = my_strdup(";")))
    return (-1);
  if (!l)
    {
      free(operator);
      free(array);
    }
  else if (l && !(getToken(operator, array, parser, &l)))
    return (-1);
  if (revParser(parser) == -1)
    return (-1);
  return (0);
}

t_lexer		*setParser(char *line)
{
  char		*token;
  char		**array;
  t_lexer	*out;
  int		i;
  int		l;
  int		first;

  i = l = first = 0;
  if (!line || !(out = getNewParser()) ||
      !(array = xcalloc(1, sizeof(*array))))
    return (NULL);
  while (line[i])
    {
      if (!(token = getTokenAt(line, &i, &first)) ||
	  !(array = getToken(token, array, out, &l)))
	return (NULL);
      if (!l && !(array = xcalloc(1, sizeof(*array))))
	return (NULL);
    }
  if (putEndCommand(line, array, out, l) == -1)
    return (NULL);
  return (out);
}
