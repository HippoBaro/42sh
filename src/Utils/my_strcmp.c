/*
** my_strcmp.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:58:32 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:58:33 2015 Hippolyte Barraud
*/

#include <42sh.h>

int	my_strcmp(char *s1, char *s2)
{
  if (s1 == NULL)
    return (-(*s2));
  if (s2 == NULL)
    return (*s1);
  while (*s1 != '\0' && *s2 != '\0')
    {
      if (*s1 == *s2)
	{
	  s1 = s1 + 1;
	  s2 = s2 + 1;
	}
      else
	return (*s1 - *s2);
    }
  if (*s1 != '\0' && *s2 == '\0')
    return (1);
  else if (*s1 == '\0' && *s2 != '\0')
    return (-1);
  return (0);
}

int my_strncmp(const char *s1, const char *s2, size_t n)
{
  if (n == 0)
	return (0);

  while (n != 0)
	{
	  if (*s1 != *s2++)
		return (*(unsigned char *) s1 - *(unsigned char *) --s2);
	  if (*s1++ == 0)
		break;
	  n--;
	}
  return (0);
}
