/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:36:16 by kblack            #+#    #+#             */
/*   Updated: 2019/03/15 12:36:47 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cd/cd ~ : HOME directory
** cd . : CURRENT directory
** cd ~username : will put you in the username's home directory; will print
**				  'cd: permission denied: PATHNAME' if no permission
** cd .. : move up 1 directory 
** cd - : switch you to previous directory 
*/

int	check_dir(char *name)
{
	DIR			*d_stream;

	d_stream = opendir(name);
	if (d_stream == NULL)
		return (-1);
	closedir(d_stream);
	d_stream = NULL;
	return (0);
}

void find_env(char *name, t_shell *sh)
{
	t_env *tmp;

	tmp = sh->env_info;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			chdir(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

int check_user(char *name, t_shell *sh)
{
	t_env *tmp;

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

void change_dir(char *arg, t_shell *sh)
{
	char *name;
	char *user;
	int tmp;

	name = NULL;
	user = NULL;
	tmp = 0;
	printf("arg ==> %s\n", arg);
	if (ft_strchr(arg, '~'))
	{
		if (arg[1])
		{
			user = ft_strsub(arg, 1, ft_strlen(arg) - 1);
			tmp = check_user(user, sh);
			if (tmp < 0)
			{
				ft_printf("cd: permission denied: /nfs/2018/%c/%s\n", arg[1], user);
				return ;
			}
		}
		name = "HOME";
		find_env(name, sh);
	}
	else if (ft_strcmp(arg, ".") == 0)
	{
		name = "PWD";
		find_env(name, sh);
	}
	else
		chdir(arg);
}

int handle_cd(char **args, t_shell *sh)
{
	char *name;

	name = NULL;
	if (args[1])
	{
		if (args[2])
			ft_printf("cd: string not in pwd: %s\n", args[1]);
		else if (check_dir(args[1]) == 0 || ft_strcmp(&args[1][0], PATH_OPT))
		{
			printf("is dir\n");
			change_dir(args[1], sh);
			// free_all_files(sh->env_info);
		}
	}
	else /* no arguments ONLY cd */
	{
		name = "HOME";
		find_env(name, sh);
	}
	return (1);
}