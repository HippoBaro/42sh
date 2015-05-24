/*
** epur_str.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:52:46 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:23:59 2015 Hippolyte Barraud
*/

#include <42sh.h>

static void	parseQuotes(char *line, char *out, int *i, int *j)
{
  char		current;
  char		currentOld;

  current = line[(*i)++];
  currentOld = 0;
  if (*j == 0 || (*j && out[(*j) - 1] != '\'' && out[(*j) - 1] != '"'))
    out[(*j)++] = current;
  else if (*j)
    {
      currentOld = out[(*j) - 1];
      --(*j);
    }
  while (line[(*i)] && line[(*i)] != current)
    out[(*j)++] = line[(*i)++];
  if (line[(*i)] == current)
    ++(*i);
  out[(*j)++] = EXISTS(currentOld, current);
  while (IS_SEP(line[*i]))
    ++(*i);
  if (IS_SEP(line[*i - 1]) && line[*i])
    out[(*j)++] = ' ';
}

static void	parseOperand(char *line, char *out, int *i, int *j)
{
  char		op;

  op = 0;
  while (line[*i] && !IS_SEP(line[*i]) && !op)
    {
      if (checkOperator(&line[*i]) != -1)
	op = 1;
      else
	out[(*j)++] = line[(*i)++];
    }
  while (IS_SEP(line[*i]))
    ++(*i);
  if (IS_SEP(line[*i - 1]) && line[*i])
    out[(*j)++] = ' ';
}

char		*formatCommand(char *line)
{
  char		*out;
  int		lenght;
  int		op;
  int		i;
  int		j;

  lenght = getCommandLenght(line);
  if (!(out = xmalloc(sizeof(*out) * (lenght + 1))))
    return (NULL);
  i = 0;
  j = 0;
  while (IS_SEP(line[i]))
    i++;
  while (line[i])
    {
      if (line[i] == '"' || line[i] == '\'')
	parseQuotes(line, out, &i, &j);
      else if ((op = checkOperator(&line[i])) != -1)
      	j += getOperator(line, &out[j], &i, op);
      else
      	parseOperand(line, out, &i, &j);
    }
  out[j] = '\0';
  free(line);
  return (out);
}
