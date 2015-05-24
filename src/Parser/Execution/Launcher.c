/*
** launcher.c for 42sh in /42sh/src/TermIO/launcher.c
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  May 13, 2015 May 13, 2015 2015 Hippolyte Barraud
** Last update Sat May 23 23:18:31 2015 Hippolyte Barraud
*/

#include <stdio.h>
#include <42sh.h>

static int	lauchCommand(t_root *cmd, int *exit_value)
{
  if (cmd->Backgrounded)
    setsid();
  envVar(cmd->Lexer2, cmd->Env);
  globInCommand(cmd->Lexer2);
  swapBylias(cmd);
  cmd->Lexer = cmd->Lexer2;
  cmd->PID = NULL;
  cmd->Lexer2 = cmd->Lexer2->Next;
  while (cmd->Lexer2 != cmd->Lexer)
    if ((*exit_value = ExecuteToken(cmd)) > 255)
      return (EXIT_VALUE(*exit_value));
  (cmd->IndexLex)++;
  disposeRoot(cmd);
  if (cmd->Backgrounded)
    return (1000);
  else
    return (-42);
}

int		handleCommandLine(t_root *cmd)
{
  int		exit_value;
  int		returnval;
  pid_t		pid;

  pid = 0;
  if (cmd->Backgrounded && (pid = xfork()) == -1)
    return (-1);
  if (pid == 0 && (returnval = lauchCommand(cmd, &exit_value)) != -42)
    return (returnval);
  if (cmd->Backgrounded)
    {
      my_putstr("[Backgrounded. PID : ");
      my_put_nbr(pid);
      my_putstr("]\n");
    }
  return (0);
}
