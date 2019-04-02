/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:09:29 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:18:06 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <string.h>

# define BUILTIN_COUNT 6
# define PATH_OPT ".~-"

# define BOLDRED			"\x1b[31;1m"
# define ANSI_COLOR_RED		"\x1b[31m"
# define BOLDMAGENTA		"\033[1m\033[31m\033[4m"
# define BOLDCYAN			"\033[1m\033[36m"
# define RESET				"\x1b[0m"
# define BACK_YELL			"\x1b[47m"

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	char			*prompt;
	char			**arr;
	char			*pwd;
	char			*line;
	struct s_env	*env_info;
}					t_shell;

typedef int	(t_fxnptr)(char**, t_shell*);

typedef struct		s_dispatch
{
	char			*key;
	t_fxnptr		*fxnptr;
}					t_dispatch;

int					execute(char **arr, t_shell *sh);
void				get_env_vars(t_shell *sh, char **envp);
void				mini_loop(t_shell *sh);

int					handle_cd(char **args, t_shell *sh);
int					handle_echo(char **args, t_shell *sh);
int					handle_env(char **args, t_shell *sh);
int					handle_exit(char **args, t_shell *sh);
int					handle_setenv(char **args, t_shell *sh);
int					handle_unsetenv(char **args, t_shell *sh);

void				free_all_files(t_env *files);
void				free_file(t_env *file);
void				free_env(char **env);
void				free_struct(t_shell *sh);
void				free_args(char **args);

void				check_args(char *str, t_shell *sh);
int					check_dir(char *name);
void				expansion(char *str, t_shell *sh);
char				*get_value(t_shell *sh, char *name);
t_env				*new_node(void);

int					check_user(char *name, t_shell *sh);
void				find_env(char *name, char *pwd, t_shell *sh);
void				check_error(char *p, char *arg);
void				tilda_handler(char *arg, t_shell *sh);
int					ft_this_list_size(t_env *begin_list);

#endif
