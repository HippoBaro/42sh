/*
** replace_alias.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:49:09 2015 Hippolyte Barraud
** Last update Sat May 23 23:07:14 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	replaceAlias(t_lexer *lex, char **aliases)
{
  char		**new;
  int		j;
  int		i;

  new = xmalloc(sizeof(char *) * (getArraySize(aliases)
				  + getArraySize(lex->CmdTab)));
  if (!new)
    return (-1);
  i = 0;
  j = 0;
  while (aliases[j] != NULL)
    new[i++] = my_strdup(aliases[j++]);
  free(lex->CmdTab[0]);
  j = 1;
  while (lex->CmdTab && lex->CmdTab[j])
    new[i++] = lex->CmdTab[j++];
  new[i] = NULL;
  free(lex->CmdTab);
  lex->CmdTab = new;
  return (0);
}

static void	findAlias(t_lexer *lex, t_alias *aliases)
{
  t_alias	*current;

  current = aliases->Next;
  while (current != aliases)
    {
      if (my_strcmp(lex->CmdTab[0], current->Name) == 0)
	replaceAlias(lex, current->Args);
      current = current->Next;
    }
}

int		swapBylias(t_root *root)
{
  t_lexer	*lex;

  lex = root->Lexer2->Next;
  while (lex != root->Lexer2)
    {
      findAlias(lex, root->Aliases);
      lex = lex->Next;
    }
  return (0);
}
