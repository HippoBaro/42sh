/*
** get_alias_elem.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:48:07 2015 Hippolyte Barraud
** Last update Sun Mar  8 01:14:49 2015 Hippolyte Barraud
*/

#include <42sh.h>

char   	*getAliasFile(t_env *env)
{
  char 	*file;
  char 	*dir;

  dir = getEnv("HOME", env);
  if (dir == NULL)
    return (NULL);
  if (!(file = xmalloc(sizeof(char) * (my_strlen(CONFIG_FILE_NAME)
				       + my_strlen(dir) + 1))))
    return (NULL);
  my_strcpy(file, dir);
  file = my_strcat(file, CONFIG_FILE_NAME);
  return (file);
}

char   	*getAliasKey(char *line)
{
  int  	i;
  char 	*key;

  i = 0;
  while (line[i] != '\0' && line[i] != '=')
    i = i + 1;
  if (line[i] != '=')
    {
      print_error(ERROR_ALIAS_NAME);
      return (NULL);
    }
  if (!(key = xmalloc(sizeof(char) * (i + 1))))
    return (NULL);
  i = 0;
  while (line[i] != '\0' && line[i] != '=')
    {
      key[i] = line[i];
      i = i + 1;
    }
  key[i] = '\0';
  return (key);
}

char   	*getAliasValue(char *line)
{
  char 	*out;
  int  	i;
  int  	j;

  i = 0;
  while (line[i] != '\0' && line[i] != '=')
    i++;
  i++;
  j = 0;
  while (line[i] != '\0')
    {
      i++;
      j++;
    }
  if (!(out = xmalloc(sizeof(char) * (j + 1))))
    return (NULL);
  i = i - j;
  j = 0;
  while (line[i] != '\0')
    out[j++] = line[i++];
  out[j] = '\0';
  return (out);
}
