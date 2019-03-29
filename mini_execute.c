/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:13:54 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:29:38 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Dispatch table builtin commands followed by their corresponding functions
*/

struct s_dispatch builtins[BUILTIN_COUNT] = {
	{"cd", handle_cd},
	{"env", handle_env},
	{"echo", handle_echo},
	{"exit", handle_exit},
	{"setenv", handle_setenv},
	{"unsetenv", handle_unsetenv}
};

/*
** Starts a new process using the fork() & execve() system calls
*/

void		launch(char *ex, char **arr, t_shell *sh)
{
	int		status;
	pid_t	childpid;
	pid_t	wait_ret;

	childpid = fork();
	if (childpid < 0)
	{
		ft_printf("ash: unable to fork process: %d\n", childpid);
		exit(-1);
	}
	if (childpid == 0)
	{
		if (execve(ex, arr, sh->arr) == -1)
			ft_printf("ash: permission denied: %s\n", ex);
		exit(-1);
	}
	else
		wait_ret = waitpid(childpid, &status, 0);
}

void		join_path(char **p, char **arr, t_shell *sh)
{
	int		i;
	char	*tmp;
	char	*path;

	i = -1;
	while (p[++i])
	{
		tmp = ft_strjoin(p[i], "/");
		path = ft_strjoin(tmp, arr[0]);
		free(tmp);
		if (access(path, F_OK) != -1)
		{
			launch(path, arr, sh);
			free(path);
			break ;
		}
		free(path);
	}
	check_error(p[i], arr[0]);
}

/*
** Finds the path of the program to run
*/

void		find_path(char **arr, t_shell *sh)
{
	t_env	*list;
	char	**p;

	p = NULL;
	list = sh->env_info;
	while (list)
	{
		if (ft_strcmp(list->key, "PATH") == 0)
			p = ft_strsplit(list->value, ':');
		if (list->next == NULL)
			break ;
		list = list->next;
	}
	if (!p)
		return ;
	join_path(p, arr, sh);
	free_env(p);
}

/*
** Determines whether to launch a builtin or a process
*/

int			execute(char **arr, t_shell *sh)
{
	int		i;

	i = 0;
	if (arr[0] == NULL)
		return (1);
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(arr[0], builtins[i].key) == 0)
			return (builtins[i].fxnptr(arr, sh));
		i++;
	}
	(access(arr[0], F_OK) != -1) ? launch(arr[0], arr, sh) : find_path(arr, sh);
	return (1);
}
