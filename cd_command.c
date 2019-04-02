/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:36:16 by kblack            #+#    #+#             */
/*   Updated: 2019/03/28 21:37:16 by kblack           ###   ########.fr       */
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

/*
** Updates the pathnames of the current and previous working directories
*/

void		update_path(char *old, char *new, t_shell *sh)
{
	char	**arr;
	char	*ntmp;
	char	*otmp;

	arr = (char**)malloc(sizeof(char*) * 4);
	arr[1] = ft_strnew(PATH_MAX);
	arr[2] = ft_strnew(PATH_MAX);
	ntmp = ft_strjoin("PWD=", new);
	otmp = ft_strjoin("OLDPWD=", old);
	arr[0] = NULL;
	arr[1] = ft_strcpy(arr[1], ntmp);
	arr[2] = ft_strcpy(arr[2], otmp);
	arr[3] = NULL;
	handle_setenv(arr, sh);
	free(ntmp);
	free(otmp);
	free(arr[1]);
	free(arr[2]);
	free(arr);
}

/*
** Changes directories
*/

void		find_env(char *name, char *pwd, t_shell *sh)
{
	t_env	*tmp;
	char	*cur;

	tmp = sh->env_info;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
		{
			cur = tmp->value;
			chdir(tmp->value);
			update_path(pwd, tmp->value, sh);
			break ;
		}
		tmp = tmp->next;
	}
}

void		change_dir(char *arg, t_shell *sh)
{
	char	*pwd;

	pwd = get_value(sh, "PWD");
	if (ft_strchr(arg, '~'))
		tilda_handler(arg, sh);
	else if (ft_strchr(arg, '-'))
		find_env("OLDPWD", pwd, sh);
	else if (ft_strcmp(arg, ".") == 0)
		return ;
	else
	{
		if (chdir(arg) == 0)
		{
			if (ft_strcmp(arg, "..") == 0)
				update_path(pwd, get_value(sh, "HOME"), sh);
			return ;
		}
		ft_printf("cd: no such file or directory: %s\n", arg);
	}
}

int			handle_cd(char **args, t_shell *sh)
{
	if (args[1])
	{
		if (args[2])
			ft_printf("cd: string not in pwd: %s\n", args[1]);
		else if (check_dir(args[1]) == 0 || ft_strcmp(&args[1][0], PATH_OPT))
			change_dir(args[1], sh);
	}
	else
		find_env("HOME", get_value(sh, "PWD"), sh);
	return (1);
}
