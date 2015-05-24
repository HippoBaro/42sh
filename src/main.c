/*
** main.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:47:46 2015 Hippolyte Barraud
** Last update Sat May 23 23:04:27 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int     	mainTermLoop(t_root *root, struct termios *old)
{
  char 		*line;
  int	       	retval;

  while ((line = catchPrompt(root)) != NULL)
    {
      saveHistory(root->History, root->Env);
      root->Backgrounded = 0;
      if (line[my_strlen(line) - 1] == '&')
	{
	  root->Backgrounded = 1;
	  line[my_strlen(line) - 1] = '\0';
	}
      line = formatCommand(line);
      if (tcsetattr(0, 0, old) == -1)
	return (print_error(ERROR_TCSETATTR));
      if ((root->Lexer2 = setParser(line)) &&
	  (retval = handleCommandLine(root)) > 255)
	return (retval);
      displayPrompt(root);
    }
  my_putchar('\n');
  return (0);
}

static int     	standardTermLoop(t_root *root)
{
  char	       	*line;
  int	       	retval;

  while ((line = get_next_line(0)) != NULL)
    {
      root->Backgrounded = 0;
      if (line[my_strlen(line) - 1] == '&')
	{
	  root->Backgrounded = 1;
	  line[my_strlen(line) - 1] = '\0';
	}
      line = formatCommand(line);
      if ((root->Lexer2 = setParser(line)) &&
	  (retval = handleCommandLine(root)) > 255)
	return (retval);
      displayPrompt(root);
    }
  my_putchar('\n');
  return (0);
}

static t_root	*importConf(int ac, char **av,
			    char **env)
{
  t_root       	*root;

  if (!(root = getNewRoot(ac, av, env)) ||
      !(root->History = getHistory(root->Env)) ||
      !(root->Aliases = getAliases(root->Env)))
    return (NULL);
  this = getpid();
  return (root);
}

static void	display_welcome(t_root *root)
{
  my_putstr(WELCOME);
  my_putstr(SEP);
  my_putstr("\n");
  displayPrompt(root);
}

int			main(int ac, char **av, char **env)
{
  struct termios	termIO;
  t_root		*root;
  int			retval;
  char			*termdef;
  char			termDetect;

  if (!(root = importConf(ac, av, env)))
    return (EXIT_FAILURE);
  termDetect = 0;
  if (!(termdef = getEnv("TERM", root->Env)) || tgetent(NULL, termdef) != 1)
    termDetect = print_error(ERROR_TCSETATTR);
  display_welcome(root);
  if (isatty(0) == 0 || tcgetattr(0, &termIO) == -1 || termDetect == -1)
    retval = standardTermLoop(root);
  else
    {
      retval = mainTermLoop(root, &termIO);
      if (root->Backgrounded == 0)
    	tcsetattr(0, 0, &termIO);
    }
  resetFD(root->fd, 0);
  resetFD(root->fd, 1);
  free_env(root->Env);
  return (retval);
}
