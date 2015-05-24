/*
** my_list.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:53:47 2015 Hippolyte Barraud
** Last update Sat May 23 23:13:52 2015 Hippolyte Barraud
*/

#include <42sh.h>

t_pid		*addPidToList(t_pid *target, pid_t pid)
{
  t_pid		*out;

  if (!(out = xmalloc(sizeof(*out))))
    return (NULL);
  out->PID = pid;
  out->Next = target;
  return (out);
}

int		addTokenToList(t_lexer *target, char **array, char *operator)
{
  t_lexer	*add;

  if (!(add = xmalloc(sizeof(*add))))
    return (-1);
  add->CmdTab = array;
  add->init = TRUE;
  add->Op = operator;
  add->Prev = target->Prev;
  add->Next = target;
  target->Prev->Next = add;
  target->Prev = add;
  return (0);
}

void   	listDisposeNode(t_lexer *node)
{
  node->Prev->Next = node->Next;
  node->Next->Prev = node->Prev;
  if (node)
    free(node);
}
