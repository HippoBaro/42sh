##
## Makefile for minishell2 in /home/barrau_h
## 
## Made by Hippolyte Barraud
## Login   <barrau_h@epitech.net>
## 
## Started on  Sat Mar  7 01:46:49 2015 Hippolyte Barraud
## Last update Sat May 23 23:32:55 2015 Hippolyte Barraud
##

CC		=	gcc

NAME		=	42sh

TERMIO		=	src/TermIO/
AUTOGUESS	= 	$(TERMIO)Autoguess/
PROMPT		= 	$(TERMIO)Prompt/
SHORTCUTS	= 	$(TERMIO)Shortcuts/

PARSER		=	src/Parser/
EXEC		=	$(PARSER)Execution/
EXECUTIL	=	$(PARSER)Utils/
EXECPATH	=	$(PARSER)Path/

FEAT		=	src/Feat/
HISTORY		=	$(FEAT)History/
ALIAS		=	$(FEAT)Alias/
ENV		=	$(FEAT)ENV/

BONUS		=	Bonus/

UTILS		=	src/Utils/

SRC		= 	src/main.c				\
		  	$(AUTOGUESS)Display.c			\
		  	$(AUTOGUESS)Check.c			\
			$(AUTOGUESS)Get.c			\
			$(AUTOGUESS)GetSize.c			\
			$(AUTOGUESS)Autoguess.c			\
			$(AUTOGUESS)Sort.c			\
			$(PROMPT)Prompt.c			\
			$(PROMPT)Display.c			\
			$(PROMPT)Delete.c			\
			$(PROMPT)Move.c				\
			$(PROMPT)Put.c				\
			$(SHORTCUTS)Shorcuts.c			\
			$(TERMIO)DisposeRoot.c			\
			$(TERMIO)Init.c				\
			$(TERMIO)Globbing.c			\
		  	$(EXEC)Launcher.c			\
		  	$(EXEC)Exec.c				\
		  	$(EXEC)Pipe.c				\
		  	$(EXECUTIL)TokenLen.c			\
		  	$(EXECUTIL)Format.c			\
		  	$(EXECPATH)GetPath.c			\
		  	$(EXECPATH)ToArray.c			\
		  	$(PARSER)Get.c				\
		  	$(PARSER)List.c				\
		  	$(PARSER)Operators.c			\
		  	$(PARSER)Syntax.c			\
		  	$(PARSER)Waiter.c			\
		  	$(PARSER)Redirections.c			\
		  	$(PARSER)Init.c				\
		  	$(PARSER)ParserLogic.c			\
		  	$(FEAT)FeatCd.c				\
		  	$(FEAT)Feats.c				\
		  	$(FEAT)FeatEcho.c			\
		  	$(FEAT)FeatExit.c			\
		  	$(HISTORY)Feat.c			\
		  	$(HISTORY)List.c			\
		  	$(HISTORY)GetSet.c			\
		  	$(HISTORY)Browser.c			\
		  	$(HISTORY)Put.c				\
		  	$(ALIAS)Parser.c			\
		  	$(ALIAS)Set.c				\
		  	$(ALIAS)Feat.c				\
		  	$(ALIAS)Helper.c			\
		  	$(ALIAS)Get.c				\
		  	$(ALIAS)Dispose.c			\
		  	$(ENV)Set.c				\
		  	$(ENV)Vars.c				\
		  	$(ENV)Feat.c				\
		  	$(ENV)List.c				\
		  	$(ENV)ToArray.c				\
		  	$(UTILS)my_putchar.c			\
		  	$(UTILS)my_putstr.c			\
		  	$(UTILS)my_strncpy.c			\
		  	$(UTILS)my_strlen.c			\
		  	$(UTILS)my_strcat.c			\
		  	$(UTILS)my_put_nbr.c			\
		  	$(UTILS)my_getnbr.c			\
		  	$(UTILS)my_strcmp.c			\
		  	$(UTILS)my_strcpy.c			\
		  	$(UTILS)my_strdup.c			\
		  	$(UTILS)xmalloc.c			\
		  	$(UTILS)xfork.c				\
		  	$(UTILS)get_next_line.c			\
		  	$(UTILS)xcalloc.c			\
		  	$(UTILS)my_tablen.c			\
		  	$(UTILS)my_freetab.c			\
		  	$(BONUS)AsciiST.c			\
		  	$(BONUS)StillAlive.c			\

OBJ		=	$(SRC:.c=.o)

CFLAGS		+=	-I./includes/
CFLAGS		+= 	-Wno-overlength-strings
CFLAGS		+=	-W -Wall -Wextra -Werror -pedantic

CLIBS		=	-lncurses -lSDL -lSDL_mixer

RM		=	rm -f

all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) -o $(NAME) $(OBJ) $(CLIBS)

clean		:
			$(RM) $(OBJ)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
