/*
** minishell2.h for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:47:31 2015 Hippolyte Barraud
** Last update Sat May 23 23:03:43 2015 Hippolyte Barraud
*/

#ifndef _42SH_H_
# define _42SH_H_

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <glob.h>
#include "get_next_line.h"

# define PRD_NAME      		"ShugarSh"

# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define CYAN			"\033[36m"
# define BLUE		   	"\033[34m"
# define YELLOW			"\033[33m"
# define BLANK		 	"\033[0m"

# define LEFT			"\033[D"
# define RIGHT			"\033[C"
# define DEL			"\033[3~"
# define UP		       	"\033[A"
# define DOWN			"\033[B"
# define EOT			"\004"
# define TAB			"\011"
# define BACKSPACE		"\177"

# define CTRL_L			"\014"
# define CTRL_R			"\022"
# define PAGE_UP		"\033[5~"
# define PAGE_DOWN		"\033[6~"

# define TRUE			1
# define FALSE			0

# define CONFIG_FILE_NAME	"/." PRD_NAME "rc"
# define HISTORY_FILE_NAME	"/." PRD_NAME ".history"

# define HISTORY_MAX		1000

# define ERROR_ALIAS_NAME	"Invalid alias name\n"
# define ERROR_OPEN_CONFIG_FILE	"Open of " CONFIG_FILE_NAME " failed\n"
# define ERROR_OPEN_HISTORY_FILE	"Open of " HISTORY_FILE_NAME " failed\n"
# define ERROR_ALIAS_404	"Alias not found\n"
# define ERROR_UNSETENV_404	" : not found\n"
# define ERROR_SETENV_CANTSET	"Cannot change environment variable\n"
# define ERROR_SETENV_CANTGET	"Cannot retrieve environment variable\n"
# define ERROR_CD_CANT_ACCES	"cd : Cannot access "
# define ERROR_CD_404		": No such file or directory\n"
# define ERROR_CD_NOTDIR	": Not a directory\n"
# define ERROR_CD_403		": Permission denied\n"
# define ERROR_ACCES_HOME	": Cannot read home folder.\n"
# define ERROR_DUP2    		": dup2 failed.\n"
# define ERROR_PIPE    		": pipe failed.\n"
# define ERROR_CLOSE		": close failed.\n"
# define ERROR_OPEN	       	": open failed.\n"
# define ERROR_SIGNAL		": signal failed\n"
# define ERROR_FORK	       	": fork failed.\n"
# define ERROR_MALLOC		": malloc failed.\n"
# define ERROR_TCSETATTR	": tcsetattr failed.\n"
# define ERROR_EXEC_ISDIR	": is a directory.\n"
# define ERROR_EXEC_CMD_NOTFOUND	": Command not found.\n"
# define ERROR_GET_PATH		"Failed to get path in tab.\n"
# define ERROR_SYNTAX		" : syntax error near unexpected token '"
# define ERROR_FATAL		"\nOk...\nJe vais faire du café. Revenez plus \
tard.\n"
# define ERROR_GLOB	       	": glob failed.\n"

# define SIGNAL_SIGQUIT		"Quit\n"
# define SIGNAL_SIGILL		"Illegal Instruction\n"
# define SIGNAL_SIGABRT		"Aborted\n"
# define SIGNAL_SIGFPE		"Floating point exception\n"
# define SIGNAL_SIGSEGV		"Segmentation fault\n"
# define SIGNAL_EOT	       	"Exit : End of Transmission"

# define ALIAS_USAGE		"Usage : alias [name] [value]\n"
# define SETENV_USAGE		"Usage : my_setenv [key] [value]\n"
# define UNSETENV_USAGE		"Usage : unsetenv [key]\n"

# define SEP			"---------------------------------------\
----------------------------------------\n"

# define WELCOME	       	GREEN "Welcome in ShugarSh. This is a \
rather simple shell. Use 'exit' to quit and return to your ridiculously \
sophisticated shell. 'cd', 'setenv', 'unsetenv', 'env', 'pwd', \
'alias', 'unalias' and 'history' are built-in and works just \
fine.\n" BLANK

# define APERTURE 	             		  \
  "              .,-:;//;:=,		       	\n\
          . :H@@@MM@M#H/.,+%;,		       	\n\
       ,/X+ +M@@M@MM%=,-%HMMM@X/,	       	\n\
     -+@MM; $M@@MH+-,;XMMMM@MMMM@+-	        \n\
    ;@M@@M- XM@X;. -+XXXXXHHH@M@M#@/.		\n\
  ,%MM@@MH ,@%=             .---=-=:=,.		\n\
  =@#@@@MX.,                -%HX$$%%%:;		\n\
 =-./@M@M$                   .;@MMMM@MM:	\n\
 X@/ -$MM/                    . +MM@@@M$	\n\
,@M@H: :@:                    . =X#@@@@-	\n\
,@@@MMX, .                    /H- ;@M@M=	\n\
.H@@@@M@+,                    %MM+..%#$.	\n\
 /MMMM@MMH/.                  XM@MH; =;		\n\
  /%+%$XHH@$=              , .H@@@@MX,		\n\
   .=--------.           -%H.,@@@@@MX,		\n\
   .%MM@@@HHHXX$$$%+- .:$MMX =M@@MM%.		\n\
     =XMMM@MM@MM#H;,-+HMM@M+ /MMMX=	       	\n\
       =%@M@M#@$-.=$@MM@@@M; %M%=	       	\n\
         ,:+$+-,/H#MMMMMMM@= =,		       	\n\
               =++%%%%+/:-.		       	\n\
					       	\n\
Forms FORM-29827281-12:			       	\n\
Test Assessment Report			      \n\n"

typedef int		pid_t;

typedef struct		s_lexer
{
  char			**CmdTab;
  char			*Op;
  int			init;
  struct s_lexer	*Prev;
  struct s_lexer	*Next;
}			t_lexer;

typedef struct		s_error
{
  int			Value;
  char			*Desc;
}			t_error;

typedef struct		s_alias
{
  char			*Name;
  char			**Args;
  struct s_alias	*Next;
  struct s_alias	*Prev;
}			t_alias;

typedef struct		s_exe
{
  char			*Name;
  struct s_exe		*Next;
  struct s_exe		*Prev;
}			t_exe;

typedef struct		s_feat
{
  char			*FeatCmd;
  int			(*ptr)();
}			t_feat;

typedef struct		s_key
{
  char			*KeyCmd;
  char			*(*ptr)();
}			t_key;

typedef struct		s_env
{
  char			*Key;
  char			*Value;
  struct s_env		*Next;
  struct s_env		*Prev;
}			t_env;

typedef struct		s_pid
{
  pid_t			PID;
  struct s_pid		*Next;
  struct s_pid		*Prev;
}			t_pid;

typedef struct		s_history
{
  char			*Value;
  int			Index;
  struct s_history     	*Next;
  struct s_history     	*Prev;
}			t_history;

typedef struct		s_root
{
  t_pid			*PID;
  pid_t			HostPID;
  t_env			*Env;
  t_lexer		*Lexer;
  t_lexer		*Lexer2;
  char			**CmdArray;
  int			IndexLex;
  int			fd[3];
  int			Backgrounded;
  t_history		*History;
  t_alias		*Aliases;
}			t_root;

typedef struct		s_pipe
{
  int			Op;
  int			(*ptr)(t_root *FeatCmd);
}			t_pipe;
pid_t			this;

# define IS_SEP(x)	((x > 0 && x < 33) || x > 126 ? 1 : 0)
# define EXIT_VALUE(x)	(((x + 256) % 256) + 256)
# define EXISTS(a, b)	(a ? a : b)

/*
** UTILS
*/
void		my_putchar(char c);
void		my_putchar_fd(char c, int fd);
void		my_putstr(char *str);
void		my_putstr_fd(char *str, int fd);
int		print_error(char *str);
int		my_strlen(const char *str);
int		my_getnbr(char *str);
int		my_strcmp(char *s1, char *s2);
int		my_strncmp(const char *s1, const char *s2, size_t n);
void		my_put_nbr(int nbr);
void		my_put_nbr_fd(int nb, int fd);
char		*my_strcpy(char *dest, char *src);
char		*my_strncpy(char *dest, char *src, int n);
char		*my_strdup(char *src);
void		*xmalloc(size_t size);
void		*xcalloc(size_t nmemb, size_t size);
void		my_put_nbr(int nb);
int		my_tablen(char **ptr);
int		my_freetab(char **ptr);
char		*get_next_line(const int fd);
char		*my_strcat(char *dest, char *src);
pid_t		xfork(void);
void		*my_memset(void *dst, int c, size_t n);

/*
** BUILTINS
*/
char		*getAliasFile(t_env *env);
char		*getAliasKey(char *line);
char		*getAliasValue(char *line);
int		cdFeat(t_root *cmd);
int		alias(t_root *root);
int		setAlias(t_alias *alias, char *alias_name, char *value);
t_alias		*getAliases(t_env *env);
int		echoFeat(t_root *cmd);
int		envFeat(t_root *root);
int		envVar(t_lexer *parser, t_env *env);
int		exitFeat(t_root *cmd);
int		setEnv(t_env *env, char *key, char *value);
int		FeatEnv(t_root *cmd);
int		unalias(t_root *root);
int		unSetEnv(t_root *root);
char		**parseAlias(char *str);
char		*search_up(int *index, char *str, t_root *cmd);
int	       	my_AsciiST(t_root *cmd);

/*
** PARSING
*/
int		assignCommand(t_root *cmd);
int		executeCommand(t_root *cmd);
t_env		*arrayToList(char **envp);
int		stopRedirectionHandler(char *str);
int		getCommandLenght(char *str);
char		*formatCommand(char *str);
int		ExecuteToken(t_root *cmd);
int		handlePipe(t_root *cmd);
int		executeNextToken(t_root *cmd, int status, int op);
int		handleCommandLine(t_root *cmd);
int		redirectDelimiter(t_root *cmd);
int		redirectAppendToFile(t_root *cmd);
int		checkRedirections(t_root *cmd, int op);
int		redirectFromFile(t_root *cmd);
int		redirectToFile(t_root *cmd);
char		**getPaths(t_env *env);
int		unexpectedOperator(char *operator);
int		cmd_not_found(char *path, char **paths, char **cmdtab);
int		findCommand(char **paths, char **cmdtab);
t_root		*getNewRoot(int argc, char **argv, char **envp);
t_lexer		*getNewParser(void);
char		**listToArray(t_env *env);
int		checkFeats(t_root *cmd);
int		displayChildreenError(int status);
char		*getEnv(char *key, t_env *env);
int		addTokenToList(t_lexer *elem, char **, char *op);
t_pid		*addPidToList(t_pid *list_pid, pid_t pid);
void		listDisposeNode(t_lexer *parser);
int		checkOperator(char *str);
int		getOperator(char *str, char *newstr, int *i, int op);
void		operatorLenght(char *str, int *i, int *size, int op);
char		**pathToArray(char *str);
int		getTokenLenght(char *str);
t_lexer		*setParser(char *str);
int		swapBylias(t_root *root);
void		resetFD(int *fd, int i);
int		revParser(t_lexer *parser);

/*
** TERMIO
*/
char		*printHistory(int *index, char *str, t_root *cmd);
char		*clearTerminal(int *index, char *str, t_root *cmd);
int		autoguessExes(t_root *cmd, char *line, t_exe *bin);
int		putExeInAutoguess(t_exe *bin, char *name);
char		*autoguess(int *index, char *str, t_root *cmd);
char		*getBin(char *str, int *index, int star);
int		autoguessInFiles(char *str, int *index, t_exe *bin, int star);
int		isAlphanum(char c);
int		isFirstWord(char *str, int index);
int		isInExes(char *str, t_exe *bin);
void		disposeExes(t_exe *bin);
void		disposeRoot(t_root *cmd);
void		free_env(t_env *env);
void		disposeLastExes(t_exe *bin);
void		disposeHistoryList(t_history *hist);
char		*handleDeleteKey(int *index, char *str, t_root *cmd);
char		*handleSuprKey(int *index, char *str, t_root *cmd);
char		*tabReturn(int *index, char *str, t_root *cmd);
char		*handleHistoryDownKey(t_root *cmd, int *index,
				      int *hist_elem, char *str);
char		*handleLeftKey(int *index, char *str, t_root *cmd);
char		*handleRightKey(int *index, char *str, t_root *cmd);
char		*handleHistoryUpKey(t_root *cmd, int *index,
				    int *hist_elem, char *str);
char		*getHistoryNode(int hist_elem, t_history *hist, int *flag);
int		clearHistory(t_history *hist, char flag);
int		hitoryListCount(t_history *hist);
void		disposeHistoryNode(t_history *hist);
char		*handleEdition(int *index, char *c, char *str);
int		getLittleLenght(t_exe *bin);
int		getNewSize(t_exe *bin);
int		lineHasGlob(char *str);
int		globInCommand(t_lexer *parser);
int		getArraySize(char **);
char		*checkLastHistory(t_history *hist, char *str);
int		featHistory(t_root *cmd);
int		my_easteregg(t_root *cmd);
int		saveHistory(t_history *hist, t_env *env);
t_history      	*getHistory(t_env *env);
t_history      	*initHistory(void);
char		*getHistoryFile(t_env *env);
char		*initTermLine(int *index);
int		is_empty(char *str);
int		bonus(t_root *cmd);
char		*historyCpy(char *dest, char *src);
int		import(t_root *cmd);
int		exesLenght(t_exe *bin);
void		checkAutoguessLenght(t_exe *bin, int size);
void		printGuess(t_exe *bin);
char		*catchPrompt(t_root *cmd);
int		displayPrompt(t_root *cmd);
char		*putStringInPrompt(char *str, int index, char *c);
int		putNodeInHistorySecure(t_history *hist, char *data);
int		putNodeInHistory(t_history *hist, char *data);
int		sortExes(t_exe *bin);

#endif /* !_42SH_H_ */
