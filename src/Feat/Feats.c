/*
** my_builtins.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:50:55 2015 Hippolyte Barraud
** Last update Sat May 23 23:05:30 2015 Hippolyte Barraud
*/

#include <42sh.h>

static const t_feat	Feats[] =
  {
    {"setenv", &FeatEnv},
    {"unsetenv", &unSetEnv},
    {"echo", &echoFeat},
    {"exit", &exitFeat},
    {"env", &envFeat},
    {"history", &featHistory},
    {"cd", &cdFeat},
    {"alias", &alias},
    {"unalias", &unalias},
    {"import", &import},
    {"StillAlive", &my_easteregg},
    {"StarWars", &my_AsciiST}
  };

int		unfound(t_root *root)
{
  (void)root;
  return (-2);
}

int    	checkFeats(t_root *root)
{
  int  	i;
  int  	exit;

  i = 0;
  while (i < 12)
    {
      if (my_strcmp(Feats[i].FeatCmd, root->CmdArray[0]) == 0)
	{
	  exit = Feats[i].ptr(root);
	  resetFD(root->fd, 1);
	  return (exit);
	}
      ++i;
    }
  return (-2);
}
