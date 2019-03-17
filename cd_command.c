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

int handle_cd(char **args)
{
	if (args[1])
	{
		if (args[2])
			ft_printf("cd: string not in pwd: %s\n", args[1]);
		else if (check_dir(args[1]) == 0)
			printf("This is a DIR\n");
	}
		// chdir(args[1]);
	return (1);
}