/*
** reverse_syntax.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:54:33 2015 Hippolyte Barraud
** Last update Sat May 23 23:15:39 2015 Hippolyte Barraud
*/

#include <42sh.h>

int	unexpectedOperator(char *operator)
{
  print_error(PRD_NAME ERROR_SYNTAX);
  print_error(operator);
  print_error("'\n");
  return (-1);
}

static int	copyTokenCmdArray(t_lexer *src, t_lexer *dest)
{
  int		i;
  int		srcSize;
  int		destSize;

  srcSize = my_tablen(src->CmdTab);
  destSize = my_tablen(dest->CmdTab);
  if (srcSize > 1)
    {
      if (!(dest->CmdTab = realloc(dest->CmdTab, (destSize + srcSize + 1)
				   * sizeof(*(dest->CmdTab)))))
	return (-1);
      i = 1;
      while (i < srcSize && src->CmdTab[i])
	dest->CmdTab[destSize++] = src->CmdTab[i++];
      dest->CmdTab[destSize] = NULL;
      src->CmdTab[1] = NULL;
    }
  return (0);
}

static int	checkParser(t_lexer *parser)
{
  t_lexer	*tmp;

  tmp = parser->Next;
  while (tmp != parser)
    {
      if (!(tmp->CmdTab[0]))
	return (unexpectedOperator(tmp->Op));
      tmp = tmp->Next;
    }
  return (0);
}

int		revParser(t_lexer *parser)
{
  t_lexer	*current;
  t_lexer	*tocopy;
  int		operator;

  current = parser->Next;
  while (current != parser)
    {
      operator = checkOperator(current->Op);
      tocopy = current;
      if (operator > 3 && operator < 8)
	while (operator > 3 && operator < 8)
	  {
	    if (current->Next == parser ||
		copyTokenCmdArray(current->Next, tocopy) == -1)
	      return (unexpectedOperator(current->Op));
	    current = current->Next;
	    operator = checkOperator(current->Op);
	  }
      else
	current = current->Next;
    }
  if (checkParser(parser) == -1)
    return (-1);
  return (0);
}
