/*
** xmalloc.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:59:34 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:59:35 2015 Hippolyte Barraud
*/

#include <42sh.h>

void *my_memset(void *dst, int c, size_t n)
{
  char *d;

  if (n)
	{
	  d = dst;
	  while (n)
		{
		  *d++ = c;
		  n--;
		}
	}
  return dst;
}

void	*xmalloc(size_t size)
{
  void	*ptr;

  ptr = malloc(size);
  if (ptr)
    return (ptr);
  print_error(ERROR_MALLOC);
  return (NULL);
}
