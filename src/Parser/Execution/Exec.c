/*
** exec.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:51:54 2015 Hippolyte Barraud
** Last update Sat May 23 23:16:36 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	executeToken(t_root *root, int op)
{
  int		exit;

  if (op != 3)
    {
      if ((exit = checkFeats(root)) != -2)
	{
	  if (exit > 255)
	    return (exit);
	  else
	    executeNextToken(root, exit,
			     checkOperator(root->Lexer2->Op));
	}
      else if (exit == -2 && assignCommand(root) == -2)
	return (EXIT_VALUE(-1));
    }
  else if (handlePipe(root) == -2)
    return (EXIT_VALUE(-1));
  return (0);
}

int    	ExecuteToken(t_root *root)
{
  int  	operator;
  int  	exit;

  root->CmdArray = root->Lexer2->CmdTab;
  operator = checkOperator(root->Lexer2->Op);
  if (operator > 3 && operator < 8
      && (operator = checkRedirections(root, operator)) == -1)
    return (0);
  if ((exit = executeToken(root, operator)) != 0)
    return (exit);
  if (operator == 1 || operator == 8)
    {
      resetFD(root->fd, 0);
      resetFD(root->fd, 1);
      root->Lexer2 = root->Lexer2->Next;
    }
  return (0);
}
