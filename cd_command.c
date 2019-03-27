/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:36:16 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:22:53 by kblack           ###   ########.fr       */
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

void		tilda_handler(char *arg, char *name, t_shell *sh)
{
	char	*user;
	int		tmp;

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
	name = "HOME";
	find_env(name, get_value(sh, "PWD"), sh);
}

void		change_dir(char *arg, t_shell *sh)
{
	char	*name;

	name = NULL;
	if (ft_strchr(arg, '~'))
		tilda_handler(arg, name, sh);
	else if (ft_strchr(arg, '-'))
	{
		name = "OLDPWD";
		find_env(name, get_value(sh, "PWD"), sh);
	}
	else if (ft_strcmp(arg, ".") == 0)
	{
		name = "PWD";
		find_env(name, get_value(sh, "PWD"), sh);
	}
	else
	{
		if (chdir(arg) == 0)
		{
			update_path(get_value(sh, "PWD"), sh);
			return ;
		}
		ft_printf("cd: no such file or directory: %s\n", arg);
	}
}

int			handle_cd(char **args, t_shell *sh)
{
	char	*name;

	name = NULL;
	if (args[1])
	{
		if (args[2])
			ft_printf("cd: string not in pwd: %s\n", args[1]);
		else if (check_dir(args[1]) == 0 || ft_strcmp(&args[1][0], PATH_OPT))
			change_dir(args[1], sh);
	}
	else
	{
		name = "HOME";
		find_env(name, NULL, sh);
	}
	return (1);
}
