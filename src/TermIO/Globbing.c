/*
** globbing.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:56:09 2015 Hippolyte Barraud
** Last update Sat May 23 23:22:13 2015 Hippolyte Barraud
*/

#include <42sh.h>

int    	lineHasGlob(char *line)
{
  int  	i;

  if (line == NULL)
    return (0);
  i = 0;
  while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
    {
      if (line[i] == '*')
	return (1);
      i++;
    }
  return (0);
}

static int	putGlobInArray(t_lexer *parser, int i, glob_t globresult)
{
  char		**out;
  int		l;
  int		j;

  out = xmalloc(sizeof(char *) * ((int)globresult.gl_pathc
				  + getArraySize(parser->CmdTab)));
  if (!out)
    return (-1);
  l = -1;
  while (++l < i)
    out[l] = parser->CmdTab[l];
  j = 0;
  while (j < (int)globresult.gl_pathc)
    out[l++] = globresult.gl_pathv[j++];
  free(parser->CmdTab[i++]);
  while (parser->CmdTab[i])
    out[l++] = parser->CmdTab[i];
  out[l] = NULL;
  free(parser->CmdTab);
  parser->CmdTab = out;
  return (0);
}

static int	findGlobMatch(t_lexer *parser, int i)
{
  glob_t	globresult;
  int		retval;

  if (lineHasGlob(parser->CmdTab[i]) == 0)
    return (0);
  retval = glob(parser->CmdTab[i], GLOB_ERR | GLOB_TILDE |
		GLOB_MARK, NULL, &globresult);
  if (retval == GLOB_NOSPACE)
    return (print_error(ERROR_GLOB));
  if (retval == GLOB_NOMATCH || retval == GLOB_ABORTED)
    return (0);
  if ((int)globresult.gl_pathc <= 0)
    return (-1);
  if (putGlobInArray(parser, i, globresult) == -1)
    return (-1);
  return (0);
}

int		globInCommand(t_lexer *parser)
{
  t_lexer	*current;
  int		i;

  if (isatty(0) == 0)
    return (0);
  current = parser->Next;
  while (current != parser)
    {
      i = 0;
      while (current->CmdTab[i] != NULL)
	{
	  if (findGlobMatch(current, i) == -1)
	    return (-1);
	  i++;
	}
      current = current->Next;
    }
  return (0);
}
