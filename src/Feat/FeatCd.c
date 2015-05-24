/*
** my_cd.c for minishell2 in /home/barrau_h
**
** Made by Hippolyte Barraud
** Login   <barrau_h@epitech.net>
**
** Started on  Sat Mar  7 01:51:03 2015 Hippolyte Barraud
** Last update Sat May 23 23:04:49 2015 Hippolyte Barraud
*/

#include <42sh.h>

static int	displayCdAccesError(char *path)
{
  struct stat	buf;

  print_error(ERROR_CD_CANT_ACCES);
  print_error(path);
  if (lstat(path, &buf) == -1)
    print_error(ERROR_CD_404);
  else
    if ((buf.st_mode & S_IFDIR) == 0)
      print_error(ERROR_CD_NOTDIR);
    else
      print_error(ERROR_CD_403);
  return (-1);
}

static int	displayErrorDir(int error, t_root *root, char *pwd, char *old)
{
  if (error == -1 || root->CmdArray[1] == NULL)
    return (displayCdAccesError(root->CmdArray[1]));
  if (old != NULL)
    setEnv(root->Env, "OLDPWD", old);
  if (pwd != NULL)
    setEnv(root->Env, "PWD", pwd);
  if (old == NULL || pwd == NULL)
    {
      print_error(ERROR_SETENV_CANTSET);
      return (-1);
    }
  return (0);
}

static int	cdHomeDir(t_root *root)
{
  char		*homedir;
  char		*pwd;
  char		*old;

  homedir = getEnv("HOME", root->Env);
  if (homedir == NULL)
    return (print_error(ERROR_SETENV_CANTGET));
  old = getcwd(NULL, 512);
  if (chdir(homedir) == -1)
    return (print_error(ERROR_ACCES_HOME));
  pwd = getcwd(NULL, 512);
  if (old != NULL)
    setEnv(root->Env, "OLDPWD", old);
  if (pwd != NULL)
    setEnv(root->Env, "PWD", pwd);
  if (old == NULL || pwd == NULL)
    {
      print_error(ERROR_SETENV_CANTSET);
      return (-1);
    }
  return (0);
}

int	cdFeat(t_root *cmd)
{
  int	error;
  char	*pwd;
  char	*oldpwd;

  error = 0;
  if (cmd->CmdArray[1] == NULL)
    return (cdHomeDir(cmd));
  else if (my_strcmp(cmd->CmdArray[1], "-") == 0)
    {
      free(cmd->CmdArray[1]);
      if ((cmd->CmdArray[1] = my_strdup(getEnv("OLDPWD", cmd->Env))
	   ) == NULL)
	return (-1);
      my_putstr_fd(getEnv("OLDPWD", cmd->Env), cmd->fd[1]);
      my_putstr_fd("\n", cmd->fd[1]);
    }
  if (cmd->CmdArray[1] != NULL)
    {
      oldpwd = getcwd(NULL, 512);
      error = chdir(cmd->CmdArray[1]);
      pwd = getcwd(NULL, 512);
    }
  if (displayErrorDir(error, cmd, pwd, oldpwd) == -1)
    return (-1);
  return (0);
}
