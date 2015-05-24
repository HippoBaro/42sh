/*
** prompt.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:55:46 2015 Hippolyte Barraud
** Last update Sat May 23 23:28:25 2015 Hippolyte Barraud
*/

#include <42sh.h>

static const t_key	Keys[] = {
  {LEFT, &handleLeftKey},
  {RIGHT, &handleRightKey},
  {BACKSPACE, &handleDeleteKey},
  {DEL, &handleSuprKey},
  {TAB, &autoguess},
  {CTRL_L, &clearTerminal},
  {CTRL_R, &printHistory}
};

static const t_key	HistoryKeys[] = {
  {UP, &handleHistoryUpKey},
  {DOWN, &handleHistoryDownKey}
};

static int	detectKey(char *input)
{
  int		i;

  i = 0;
  while (i < 7)
    {
      if (Keys[i].KeyCmd && input)
	if (my_strncmp(Keys[i].KeyCmd, input, my_strlen(Keys[i].KeyCmd)) == 0)
	  return (i);
      ++i;
    }
  return (-1);
}

static int	detectHistoryKey(char *input)
{
  int		i;

  i = 0;
  while (i < 2)
    {
      if (HistoryKeys[i].KeyCmd && input)
	if (my_strncmp(HistoryKeys[i].KeyCmd, input,
		       my_strlen(HistoryKeys[i].KeyCmd)) == 0)
	  return (i);
      ++i;
    }
  return (-1);
}

static char	*processInput(char *input, char *line, int *i, t_root *root)
{
  int		l;

  if ((l = detectKey(input)) != -1)
    line = Keys[l].ptr(i, line, root);
  else
    {
      if ((l = detectHistoryKey(input)) != -1)
	line = HistoryKeys[l].ptr(root, i, &(root->History->Index), line);
      else if (my_strncmp(input, EOT, my_strlen(EOT)) == 0)
	{
	  disposeHistoryList(root->History);
	  return (NULL);
	}
      else if (input[0] >= ' ' && input[0] <= '~')
	line = handleEdition(i, input, line);
    }
  my_memset(input, 0, 8);
  return (line);
}

static char	*testHistory(t_root *root, char *line)
{
  char		*current;

  if (!(current = checkLastHistory(root->History, line)))
    return (line);
  line = current;
  my_putchar('\n');
  clearHistory(root->History, 0);
  return (line);
}

char   	*catchPrompt(t_root *root)
{
  char 	input[8];
  int  	ret;
  int  	i;
  char 	*line;

  root->History->Index = 0;
  if (!(line = initTermLine(&i)))
    return (NULL);
  my_memset(input, 0, 8);
  while ((ret = read(0, input, 7)) > 0 && input[0] != '\n')
    if ((line = processInput(input, line, &i, root)) == NULL)
      return (NULL);
  if (ret <= 0)
    return (NULL);
  line = testHistory(root, line);
  if (line != NULL)
    if (is_empty(line) == 0 &&
	putNodeInHistorySecure(root->History, line) == -1)
      {
	disposeHistoryList(root->History);
	return (NULL);
      }
  return (line);
}
