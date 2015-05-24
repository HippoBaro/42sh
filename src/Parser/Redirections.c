/*
** handle_redirections.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:53:11 2015 Hippolyte Barraud
** Last update Sat May 23 23:15:07 2015 Hippolyte Barraud
*/

#include <42sh.h>

static const t_pipe	Redirections[] =
  {
    {4, &redirectDelimiter},
    {5, &redirectFromFile},
    {6, &redirectAppendToFile},
    {7, &redirectToFile}
  };

int    	redirectDelimiter(t_root *root)
{
  char 	*line;

  resetFD(root->fd, 0);
  if ((root->fd[0] = open("." PRD_NAME ".tmp", O_WRONLY | O_CREAT | O_TRUNC,
			  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    return (print_error(ERROR_OPEN));
  my_putstr("> ");
  while ((line = get_next_line(0)))
    {
      if (!my_strcmp(line, root->Lexer2->Next->CmdTab[0]) ||
	  stopRedirectionHandler(line))
	{
	  free(line);
	  break ;
	}
      write(root->fd[0] , line, my_strlen(line));
      write(root->fd[0] , "\n", 1);
      free(line);
      my_putstr("> ");
    }
  if (close(root->fd[0]) == -1)
    return (-1);
  if ((root->fd[0] = open("." PRD_NAME ".tmp", O_RDONLY)) < 0)
    return (print_error(ERROR_OPEN));
  return (0);
}

int    	redirectFromFile(t_root *root)
{
  int  	fd;

  resetFD(root->fd, 0);
  if ((fd = open(root->Lexer2->Next->CmdTab[0], O_RDONLY)) < 0)
    return (print_error(ERROR_OPEN));
  root->fd[0] = fd;
  return (0);
}

int    	redirectAppendToFile(t_root *root)
{
  int  	fd;

  resetFD(root->fd, 1);
  if ((fd = open(root->Lexer2->Next->CmdTab[0], O_WRONLY | O_CREAT | O_APPEND,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    return (print_error(ERROR_OPEN));
  root->fd[1] = fd;
  return (0);
}

int    	redirectToFile(t_root *root)
{
  int  	fd;

  resetFD(root->fd, 1);
  if ((fd = open(root->Lexer2->Next->CmdTab[0], O_WRONLY | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    return (print_error(ERROR_OPEN));
  root->fd[1] = fd;
  return (0);
}

int    	checkRedirections(t_root *root, int out)
{
  while (out > 3 && out < 8)
    {
      if (Redirections[out - 4].ptr(root) == -1)
	{
	  root->Lexer2 = root->Lexer2->Next;
	  return (-1);
	}
      root->Lexer2 = root->Lexer2->Next;
      out = checkOperator(root->Lexer2->Op);
    }
  return (out);
}
