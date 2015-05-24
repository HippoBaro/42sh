/*
** cmdlen.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:52:38 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:52:39 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		getTokenLenght(char *token)
{
  int		out;

  out = 0;
  while (token[out] && !IS_SEP(token[out]))
    out++;
  return (out);
}

static void	quoteInsideLenght(char *line, int *i, int *len)
{
  char		quote;

  quote = line[(*i)++];
  ++(*len);
  while (line[*i] && line[(*i)++] != quote)
    ++(*len);
  ++(*len);
  while (IS_SEP(line[*i]))
    ++(*i);
  if (IS_SEP(line[*i - 1]) && line[*i])
    ++(*len);
}

static void	operandLenght(char *line, int *i, int *len)
{
  char		op;

  op = 0;
  while (line[*i] && !IS_SEP(line[*i]) && !op)
    {
      if (checkOperator(&line[*i]) != -1)
	op = 1;
      else
	{
	  ++(*len);
	  ++(*i);
	}
    }
  while (IS_SEP(line[*i]))
    ++(*i);
  if (IS_SEP(line[*i - 1]) && line[*i])
    ++(*len);
}

int		getCommandLenght(char *command)
{
  int		i;
  char		op;
  int		out;

  i = 0;
  out = 0;
  while (IS_SEP(command[i]))
    i++;
  while (command[i] != '\0')
    {
      if (command[i] == '"' || command[i] == '\'')
	quoteInsideLenght(command, &i, &out);
      else if ((op = checkOperator(&command[i])) != -1)
	operatorLenght(command, &i, &out, op);
      else
	operandLenght(command, &i, &out);
    }
  return (out);
}
