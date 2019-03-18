/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:09:29 by kblack            #+#    #+#             */
/*   Updated: 2019/03/13 14:12:05 by kblack           ###   ########.fr       */
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

# define BUILTIN_COUNT 4
# define PATH_OPT ".~-"

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define BOLDCYAN			"\033[1m\033[36m"
# define RESET				"\x1b[0m"
# define BACK_YELL			"\x1b[47m"

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_shell
{
	char *display;
	char *pwd;
	struct s_env *env_info;
} t_shell;

typedef int (fxnptr_t)(char**, t_shell*);
struct s_dispatch
{
	char *key;
	fxnptr_t *fxnptr;
};

char **parse_user_input(char *line);
int execute(char **arr, t_shell *sh);

int handle_cd(char **args, t_shell *sh);
int handle_echo(char **args, t_shell *sh);
int handle_env(char **args, t_shell *sh);
int handle_exit(char **args, t_shell *sh);
int handle_setenv(char **args, t_shell *sh);
int handle_unsetenv(char **args, t_shell *sh);

void get_env_vars(t_shell *sh, char **envp);

void	free_all_files(t_env *files);

#endif
