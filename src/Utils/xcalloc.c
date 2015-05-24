/*
** xcalloc.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:59:20 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:59:21 2015 Hippolyte Barraud
*/

#include <42sh.h>

void	*xcalloc(size_t nmemb, size_t size)
{
  void	*ptr;

  ptr = xmalloc(size);
  if (ptr == NULL)
	return (NULL);
  ptr = my_memset(ptr, 0, nmemb);
  return (ptr);
}
