/*
** my_put_nbr.c for minishell2 in /home/barrau_h
** 
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
** 
** Started on  Sat Mar  7 01:58:04 2015 Hippolyte Barraud
** Last update Sat Mar  7 01:58:04 2015 Hippolyte Barraud
*/

#include <42sh.h>

void	my_put_nbr(int nb)
{
  if (nb == -2147483647 - 1)
    {
      my_putchar('-');
      my_putchar('2');
      nb = 147483648;
    }
  if (nb < 0)
    {
      my_putchar('-');
      nb = -nb;
    }
  if (nb > 9)
    my_put_nbr(nb / 10);
  my_putchar(nb % 10 + '0');
}

void	my_put_nbr_fd(int nb, int fd)
{
  if (nb == -2147483647 - 1)
    {
      my_putchar_fd('-', fd);
      my_putchar_fd('2', fd);
      nb = 147483648;
    }
  if (nb < 0)
    {
      my_putchar_fd('-', fd);
      nb = -nb;
    }
  if (nb > 9)
    my_put_nbr_fd(nb / 10, fd);
  my_putchar_fd(nb % 10 + '0', fd);
}
