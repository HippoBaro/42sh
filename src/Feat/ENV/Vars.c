/*
** my_env_var.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:49:28 2015 Hippolyte Barraud
** Last update Sat May 23 23:08:59 2015 Hippolyte Barraud
*/

#include <42sh.h>

static char	*getEnvKey(char *value)
{
  int		i;
  char		*key;

  i = 0;
  while ((value[i] > 64 && value[i] < 91) ||
	 (value[i] > 96 && value[i] < 123) ||
	 (value[i] > 47 && value[i] < 58))
    ++i;
  key = xmalloc(sizeof(*key) * (i + 1));
  i = 0;
  while ((value[i] > 64 && value[i] < 91) ||
	 (value[i] > 96 && value[i] < 123) ||
	 (value[i] > 47 && value[i] < 58))
    {
      key[i] = value[i];
      ++i;
    }
  key[i] = '\0';
  return (key);
}

static int	replaceEnvNode(t_lexer *lex, int i, int k, t_env *env)
{
  char		*new;
  char		*key;
  char		*value;

  if (!(key = getEnvKey(&(lex->CmdTab[i][k + 1]))) ||
      !(value = getEnv(key, env)))
    return (-1);
  if (!(new = xmalloc(sizeof(*new) *
		      (my_strlen(lex->CmdTab[i]) - my_strlen(key)
		       + my_strlen(value) + 1))))
    return (-1);
  my_strncpy(new, lex->CmdTab[i], k);
  if (!(new = my_strcat(new, value)))
    return (-1);
  k += my_strlen(key) + 1;
  if (!(new = my_strcat(new, &(lex->CmdTab[i][k]))))
    return (-1);
  free(key);
  free(lex->CmdTab[i]);
  lex->CmdTab[i] = new;
  return (0);
}

static int	replaceNode(t_lexer *lex, int i, t_env *env)
{
  int		k;

  k = 0;
  while (lex->CmdTab[i][k])
    {
      if (lex->CmdTab[i][k] == '$' &&
	  replaceEnvNode(lex, i, k, env) == -1)
	return (-1);
      k++;
    }
  return (0);
}

static int	replaceHomeDir(t_lexer *lex, int i, t_env *env)
{
  char		*home;

  if (lex->CmdTab[i][0] == '~')
    {
      home = getEnv("HOME", env);
      if (!(home = my_strdup(home)))
	return (-1);
      if (!(home = realloc(home, sizeof(*home) *
			   (my_strlen(home) + my_strlen(lex->CmdTab[i])))))
	return (-1);
      if (!(home = my_strcat(home, &(lex->CmdTab[i][1]))))
	return (-1);
      free(lex->CmdTab[i]);
      lex->CmdTab[i] = home;
    }
  return (0);
}

int		envVar(t_lexer *lex, t_env *env)
{
  t_lexer	*current;
  int		i;

  current = lex->Next;
  while (current != lex)
    {
      i = 0;
      while (current->CmdTab[i] != NULL)
	{
	  if (replaceNode(current, i, env) == -1 ||
	      replaceHomeDir(current, i, env) == -1)
	    return (-1);
	  i = i + 1;
	}
      current = current->Next;
    }
  return (0);
}
