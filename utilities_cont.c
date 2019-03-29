/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 13:16:27 by kblack            #+#    #+#             */
/*   Updated: 2019/03/28 21:29:04 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void			tilda_handler(char *arg, t_shell *sh)
{
	char		*user;
	int			tmp;

	user = NULL;
	tmp = 0;
	if (arg[1])
	{
		user = ft_strsub(arg, 1, ft_strlen(arg) - 1);
		tmp = check_user(user, sh);
		if (tmp < 0)
		{
			ft_printf("cd: permission denied: /nfs/2018/%c/%s\n", arg[1], user);
			free(user);
			return ;
		}
	}
	free(user);
	find_env("HOME", get_value(sh, "PWD"), sh);
}
