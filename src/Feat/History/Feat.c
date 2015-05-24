/*
** history_built_in.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:50:26 2015 Hippolyte Barraud
** Last update Sat May 23 23:09:50 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char	*getNodeInHistory(t_history *hitory, char *ref, int i,
				  int size)
{
  char		*node;

  if (&ref[1] && hitory->Value &&
      my_strncmp(&ref[1], hitory->Value, my_strlen(&ref[1])) == 0)
    {
      my_putchar('\n');
      my_putstr(hitory->Value);
      node = my_strdup(hitory->Value);
      return (node);
    }
  else if (my_getnbr(&ref[1]) > 0 && size - i == my_getnbr(&ref[1]))
    {
      my_putchar('\n');
      my_putstr(hitory->Value);
      node = my_strdup(hitory->Value);
      return (node);
    }
  else if (my_getnbr(&ref[1]) < 0 && -my_getnbr(&ref[1]) == i)
    {
      my_putchar('\n');
      my_putstr(hitory->Value);
      node = my_strdup(hitory->Value);
      return (node);
    }
  return (ref);
}

char		*checkLastHistory(t_history *history, char *str)
{
  t_history	*current;
  int		i;
  int		size;
  char		*temp;

  if (str[0] == '!')
    {
      size = hitoryListCount(history) + 1;
      i = 1;
      current = history->Prev;
      while (current != history)
	{
	  temp = getNodeInHistory(current, str, i, size);
	  if (temp != str)
	    return (temp);
	  i = i + 1;
	  current = current->Prev;
	}
      my_putchar('\n');
      print_error(str);
      print_error(": event not found\n");
      return (NULL);
    }
  return (str);
}

static int	disposeHistory(t_root *root)
{
  t_history	*current;
  int		fd;
  char		*file;

  current = root->History->Prev;
  while (current != root->History)
    {
      current = current->Prev;
      disposeHistoryNode(current->Next);
    }
  if ((file = getHistoryFile(root->Env)) == NULL)
    return (-1);
  if ((fd = open(file, O_RDWR | O_CREAT | O_TRUNC,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    return (-1);
  free(file);
  close(fd);
  return (0);
}

static void	displayHistory(t_root *root)
{
  t_history	*current;
  int		i;

  i = 0;
  current = root->History->Next;
  while (current != root->History)
    {
      my_put_nbr_fd(++i, root->fd[1]);
      my_putchar_fd('\t', root->fd[1]);
      my_putstr_fd(current->Value, root->fd[1]);
      my_putchar_fd('\n', root->fd[1]);
      current = current->Next;
    }
}

int    	featHistory(t_root *root)
{
  if (root->CmdArray[1] && my_strcmp(root->CmdArray[1], "-c") == 0)
    disposeHistory(root);
  else
    displayHistory(root);
  return (0);
}
