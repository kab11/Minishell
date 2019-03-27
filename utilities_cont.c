/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:16:27 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 13:16:30 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Updates the pathnames of the current and previous working directories
*/

void			update_path(char *pwd, t_shell *sh)
{
	char		**arr;
	char		*tmp;

	arr = (char**)malloc(sizeof(char*) * 4);
	arr[0] = NULL;
	tmp = ft_strnew(PATH_MAX);
	getcwd(tmp, PATH_MAX);
	arr[1] = ft_strjoin("PWD=", tmp);
	arr[2] = ft_strjoin("OLDPWD=", pwd);
	arr[3] = 0;
	handle_setenv(arr, sh);
	free(tmp);
	free_env(arr);
}

/*
** Changes directories
*/

void			find_env(char *name, char *pwd, t_shell *sh)
{
	t_env		*tmp;

	tmp = sh->env_info;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			chdir(tmp->value);
			update_path(pwd, sh);
			break ;
		}
		tmp = tmp->next;
	}
}

/*
** Check the name of the current user
*/

int				check_user(char *name, t_shell *sh)
{
	t_env		*tmp;

	tmp = sh->env_info;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "USER") == 0)
		{
			if (ft_strcmp(tmp->value, name) == 0)
				return (0);
		}
		tmp = tmp->next;
	}
	return (-1);
}

void			check_error(char *p, char *arg)
{
	int			i;
	int			slash;

	i = -1;
	slash = 0;
	while (arg[++i])
	{
		if (arg[i] == '/')
			slash++;
	}
	if (slash > 0 && !p)
		ft_printf("ash: no such file or directory: %s\n", arg);
	else if (!p)
		ft_printf("ash: command not found: %s\n", arg);
}
