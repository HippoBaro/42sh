/*
** AsciiST.c for 42sh in /42sh/Bonus/AsciiST.c
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  May 11, 2015 May 11, 2015 2015 Hippolyte Barraud
** Last update Sat May 23 23:01:04 2015 Hippolyte Barraud
*/

#include <42sh.h>
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <sys/ioctl.h>

# define BORDERTOP \
"       /= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\\\n\
      /= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\\\n\
    ★ |= = = = = = = = = = = = = = " YELLOW "STAR WARS" BLANK " = = = = = = = = = = = = = = =| ★ \n\
      \\= = = = = = = = Appuyez sur une touche pour quitter = = = = = = = =/\n\
       \\= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =/\n"

int FRAMESPEED;

typedef struct		s_frame
{
  char			Frame[80 * 13 + 1];
  int			TimeSpan;
}		       	t_frame;

static t_frame		*getFrame(FILE *fd)
{
  char			*tmp;
  size_t		size;
  static int		i = -1;
  int			ret;
  t_frame		*out = malloc(sizeof(t_frame));

  my_memset(out->Frame, '\0', 80 * 13 + 1);
  while (TRUE)
    {
      tmp = malloc(BUFF_SIZE);
      ret = getline(&tmp, &size, fd);
      if (ret == -1)
	return (NULL);
      i++;
      if (i == 0)
	out->TimeSpan = my_getnbr(tmp) > 1 ? my_getnbr(tmp) : 1;
      else if (i < 14)
	{
	  my_strcat(out->Frame, "       ");
	  my_strcat(out->Frame, tmp);
	}
      if (i == 13)
	{
	  i = -1;
	  break;
	}
    }
  return (out);
}

static FILE    	*GetFrameSource()
{
  FILE 		*fd;

  fd = fopen("Bonus/ST.dat", "r");
  return (fd);
}

static void	printFrame(t_frame *frame)
{
  my_putstr(tgetstr("cl", NULL));
  my_putstr(BORDERTOP "\n");
  my_putstr(frame->Frame);
  usleep(FRAMESPEED * frame->TimeSpan);
  free(frame->Frame);
}

static int usage()
{
  my_putstr("Usage : StarWars [SPEED].\nSPEED : \n\t'real' : 15 fps.\n\t'fluid' : 30 fps\n\t'fast' : 150 fps\n\t'blink' : 300 fps\n");
  return (1);
}

int _kbhit() {
  static const int STDIN = 0;
  int bytesWaiting;
  static int initialized = 0;

  if (! initialized) {
    struct termios term;
    tcgetattr(STDIN, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN, TCSANOW, &term);
    setbuf(stdin, NULL);
    initialized = 1;
  }
  ioctl(STDIN, FIONREAD, &bytesWaiting);
  return bytesWaiting;
}

int	       	my_AsciiST(t_root *cmd)
{
  FILE 		*fd = GetFrameSource();
  t_frame	*frame;

  if (cmd->CmdArray[1] == NULL)
    return (usage());
  else
    {
      if (my_strcmp(cmd->CmdArray[1], "real") == 0)
	FRAMESPEED = 66666;
      else if (my_strcmp(cmd->CmdArray[1], "fluid") == 0)
	FRAMESPEED = 33333;
      else if (my_strcmp(cmd->CmdArray[1], "fast") == 0)
	FRAMESPEED = 6666;
      else if (my_strcmp(cmd->CmdArray[1], "blink") == 0)
	FRAMESPEED = 3333;
      else
	return (usage());
    }
  my_putstr(tgetstr("vi", NULL));
  frame = NULL;
  if (fd == NULL)
    return (1);
  (void)cmd;
  while ((frame = getFrame(fd)) != NULL)
    {
      if (_kbhit())
	break;
      printFrame(frame);
    }
  fclose(fd);
  my_putstr(tgetstr("ve", NULL));
  my_putstr(tgetstr("cl", NULL));
  return (0);
}
