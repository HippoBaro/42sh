/*
** get_next_line.h for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:47:14 2015 Hippolyte Barraud
** Last update Sat May 23 23:03:57 2015 Hippolyte Barraud
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define ABS(value)	((value < 0) ? -value : value)
# define BUFF_SIZE	1024

char	*get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H_ */
