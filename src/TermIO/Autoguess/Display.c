/*
** print_binaries.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:55:19 2015 Hippolyte Barraud
** Last update Sat May 23 23:24:30 2015 Hippolyte Barraud
*/

#include <42sh.h>

int		exesLenght(t_exe *exes)
{
  t_exe		*current;
  int		out;

  out = 0;
  current = exes->Next;
  while (current != NULL)
    {
      current = current->Next;
      out++;
    }
  return (out);
}

void   	printGuess(t_exe *exes)
{
  t_exe	*current;

  current = exes->Next;
  my_putchar('\n');
  while (current != NULL)
    {
      my_putstr(current->Name);
      my_putchar('\n');
      current = current->Next;
    }
}

static void	warnManyResult(t_exe *exes, int count)
{
  char		buffer[2];
  int		result;

  buffer[0] = 0;
  buffer[1] = 0;
  my_putstr("\nDisplay all ");
  my_put_nbr(count);
  my_putstr(" possibilities ? (y or n)");
  while (buffer[0] != 'y' && buffer[0] != 'n' &&
	 buffer[0] != 'Y' && buffer[0] != 'N' &&
	 (result = read(0, buffer, 1)) > 0)
    {
      if (buffer[0] == 'y' || buffer[0] == 'Y')
	printGuess(exes);
      else if (buffer[0] == 'n' || buffer[0] == 'N')
	{
	  my_putchar('\n');
	  return;
	}
    }
  if (result <= 0)
    return;
}

void		checkAutoguessLenght(t_exe *bin, int size)
{
  char		*dl;
  char		*ch;
  char		*replace;

  if (!(dl = tgetstr("dl", NULL)))
    return;
  if (!(ch = tgetstr("ch", NULL)))
    return;
  if (!(replace = tparm(ch, 0)))
    return;
  if (size == 1)
    {
      my_putstr(dl);
      my_putstr(replace);
      return;
    }
  else if (size <= 50)
    printGuess(bin);
  else
    warnManyResult(bin, size);
}
