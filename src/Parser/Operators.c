/*
** my_operators.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:53:55 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:53:56 2015 Hippolyte Barraud
*/

#include <42sh.h>

static const char	*Operators[] =
  {
    "&&",
    "&",
    "||",
    "|",
    "<<",
    "<",
    ">>",
    ">",
    ";"
  };

int	stopRedirectionHandler(char *line)
{
  int	i;

  i = 0;
  while (line[i])
    {
      if (line[i] == 4 || (line[i] == '^' && line[++i] == 'D'))
	{
	  print_error(SIGNAL_EOT);
	  return (1);
	}
      ++i;
    }
  return (0);
}

void	operatorLenght(char *line, int *i, int *len, int op)
{
  int	lenght;

  lenght = my_strlen(Operators[op]);
  if (*i != 0 && !IS_SEP(line[(*i) - 1]))
    ++(*len);
  *i += lenght;
  *len += lenght + 1;
  while (IS_SEP(line[*i]))
    ++(*i);
}

int	getOperator(char *line, char *out, int *i, int op)
{
  int	l;
  int	j;

  l = 0;
  if (*i != 0 && !IS_SEP(line[(*i) - 1]))
    out[l++] = ' ';
  j = 0;
  while (Operators[op][j++])
    out[l++] = line[(*i)++];
  out[l++] = ' ';
  while (IS_SEP(line[*i]))
    ++(*i);
  return (l);
}

int	checkOperator(char *line)
{
  int	i;

  if (!line)
    return (-1);
  i = 0;
  while (i < (int)(sizeof(Operators) / sizeof(*Operators)))
    {
      if (!my_strncmp(line, Operators[i], my_strlen(Operators[i])))
	return (i);
      i++;
    }
  return (-1);
}
