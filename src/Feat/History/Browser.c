/*
** browser.c for 42sh in /42sh/src/Feat/history/browser.c
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  May 9, 2015 May 9, 2015 2015 Hippolyte Barraud
** Last update Sat May 23 23:09:19 2015 Hippolyte Barraud
*/

#include <stdio.h>
#include <42sh.h>

char		*search_up(int *index, char *str, t_root *cmd)
{
  t_history	*tmp;

  (void)index;
  tmp = cmd->History->Next;
  while (tmp != cmd->History)
    {
      if (my_strncmp(str, tmp->Value, my_strlen(str)) == 0)
    	{
    	  my_putstr(tgetstr("dl", NULL));
    	  displayPrompt(cmd);
    	  str = my_strdup(tmp->Value);
    	  *index = my_strlen(tmp->Value);
    	  my_putstr(str);
    	  return (str);
    	}
      tmp = tmp->Next;
    }
  return (str);
}

char	*historyCpy(char *dest, char *src)
{
  int	i;
  int	y;

  y = 0;
  i = 0;
  while (src[i] != '\0')
    {
      if (src[i] >= 32 && src[i] <= 126)
	{
	  dest[y] = src[i];
	  y++;
	}
      i++;
    }
  dest[y] = '\0';
  return (dest);
}
