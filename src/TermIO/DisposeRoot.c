/*
** free_fcts.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:55:56 2015 Hippolyte Barraud
** Last update Sat May 23 23:21:48 2015 Hippolyte Barraud
*/

#include <42sh.h>

void		free_env(t_env *env)
{
  t_env		*tmp;

  tmp = env->Next;
  while (tmp != env)
    {
      if (tmp->Key != NULL)
	free(tmp->Key);
      if (tmp->Value != NULL)
	free(tmp->Value);
      tmp = tmp->Next;
      free(tmp->Prev);
    }
  if (tmp->Key != NULL)
    free(tmp->Key);
  if (tmp->Value != NULL)
    free(tmp->Value);
  free(tmp);
}

void		disposeHistoryList(t_history *history)
{
  t_history	*current;

  current = history->Next;
  while (current != history)
    {
      if (current->Value != NULL)
	free(current->Value);
      current = current->Next;
      free(current->Prev);
    }
  if (current->Value != NULL)
    free(current->Value);
  free(current);
}

void		disposeExes(t_exe *exes)
{
  t_exe		*current;
  t_exe		*dispose;

  current = exes->Next;
  while (current != NULL)
    {
      dispose = current;
      current = current->Next;
      free(dispose);
    }
}

void		disposeLastExes(t_exe *exes)
{
  t_exe		*current;
  t_exe		*dispose;

  current = exes->Next;
  while (current != NULL)
    {
      free(current->Name);
      dispose = current;
      current = current->Next;
      free(dispose);
    }
  free(exes);
}

void		disposeRoot(t_root *root)
{
  t_lexer	*lex;

  root->CmdArray = NULL;
  lex = root->Lexer->Next;
  while (lex != root->Lexer)
    {
      my_freetab(lex->CmdTab);
      free(lex->CmdTab);
      free(lex->Op);
      lex = lex->Next;
      free(lex->Prev);
    }
  free(lex);
}
