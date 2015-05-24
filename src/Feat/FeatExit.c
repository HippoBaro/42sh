/*
** my_exit.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:51:19 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:14:07 2015 Hippolyte Barraud
*/

#include <42sh.h>

int    	exitFeat(t_root *root)
{
  int  	exit;

  if (root->CmdArray[1])
    exit = my_getnbr(root->CmdArray[1]);
  else
    exit = -1;
  return (EXIT_VALUE(exit));
}

int    	import(t_root *root)
{
  if (!(root->History = getHistory(root->Env)) ||
      !(root->Aliases = getAliases(root->Env)))
    return (1);
  return (0);
}
