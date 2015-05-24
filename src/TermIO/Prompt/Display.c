/*
** disp_prompt.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:55:37 2015 Hippolyte Barraud
** Last update Sat May 23 23:27:29 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char    	*revstr(char *s)
{
  char		*i1;
  char		*i2;
  char		*m;
  int		len;
  char		c;

  len = my_strlen(s);
  i1 = s;
  i2 = i1 + len - 1;
  m = i1 + len / 2;
  while (i1 < m)
    {
      c = *i1;
      *i1++ = *i2;
      *i2-- = c;
    }
  return (s);
}

static char    	*getLastFolder(char *pwd)
{
  int		len;
  int		i;
  int		o;
  static char	out[2048];

  len = my_strlen(pwd);
  i = len - 1;
  o = 0;
  while (i >= 0)
    {
      if (pwd[i] == '/')
	break;
      else
	out[o++] = pwd[i];
      i--;
    }
  out[o] = '\0';
  return ((char*)&out);
}

static void	promptNoEnv(void)
{
  my_putstr(RED);
  my_putstr("No ENV ~ Most features disabled");
  my_putstr(BLANK);
}

int    	displayPrompt(t_root *root)
{
  char 	*pwd;
  char 	*user;

  user = getEnv("USER", root->Env);
  pwd = getEnv("PWD", root->Env);
  my_putstr(CYAN);
  my_putchar('[');
  if (user != NULL && pwd != NULL)
    {
      my_putstr(CYAN);
      my_putstr(user);
      my_putstr(BLANK);
      my_putstr(BLUE);
      my_putchar('@');
      my_putstr(BLANK);
      my_putstr(CYAN);
      my_putstr(revstr(getLastFolder(pwd)));
      my_putstr(BLANK CYAN);
    }
  else
    promptNoEnv();
  my_putstr("] ");
  my_putstr(BLANK);
  return (0);
}

char	*handleEdition(int *i, char *toadd, char *line)
{
  my_putstr(tgetstr("im", NULL));
  my_putstr(toadd);
  if ((line = putStringInPrompt(line, *i, toadd)) == NULL)
    return (NULL);
  *i = *i + my_strlen(toadd);
  my_putstr(tgetstr("ei", NULL));
  return (line);
}
