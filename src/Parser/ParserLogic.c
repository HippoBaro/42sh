/*
** handle_next_cmd.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:53:02 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:25:07 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	operatorAnd(t_root *root, int state)
{
  if (state == 0)
    root->Lexer2 = root->Lexer2->Next;
  else
    {
      while (my_strcmp(root->Lexer2->Op, ";") != 0 &&
	     my_strcmp(root->Lexer2->Op, "||") != 0)
	{
	  if (root->Lexer2 == root->Lexer)
	    return (-1);
	  root->Lexer2 = root->Lexer2->Next;
	}
      root->Lexer2 = root->Lexer2->Next;
    }
  return (0);
}

static int	operatorOr(t_root *root, int state)
{
  if (state != 0)
    root->Lexer2 = root->Lexer2->Next;
  else
    {
      while (my_strcmp(root->Lexer2->Op, ";") != 0 &&
	     my_strcmp(root->Lexer2->Op, "&&") != 0)
	{
	  if (root->Lexer2 == root->Lexer)
	    return (-1);
	  root->Lexer2 = root->Lexer2->Next;
	}
      root->Lexer2 = root->Lexer2->Next;
    }
  return (0);
}

int    	executeNextToken(t_root *root, int state, int op)
{
  if (op == 0)
    return (operatorAnd(root, state));
  else if (op == 2)
    return (operatorOr(root, state));
  return (0);
}
