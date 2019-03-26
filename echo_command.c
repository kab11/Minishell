/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:38:36 by kblack            #+#    #+#             */
/*   Updated: 2019/03/15 12:38:46 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

expansion()
{

}

void check_args(char *arg)
{
	int j;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '"' || arg[j] == '\'' || arg[j] == '\\')
			j++;
		if (arg[j] == '$' || arg[j] == '~')
			expansion();
		ft_printf("%c", arg[j]);
		j++;
	}
}

int handle_echo(char **args, t_shell *sh)
{
	int i;

	i = 1;
	(void)sh;
	while (args[i])
	{
		check_args(args[i]);
		i++;
	}
	if (i > 1)
		write(1, "\n", 1);
	return (1);
}

/* Handle "" and '' */
	// int i;
	// int wd_len;

	// i = 0;
	// wd_len = 0;
	// while (args[i] != NULL)
	// 	i++;
	// i--;
	// wd_len = ft_strlen(args[i]);
	// if ((args[1][0] == '\"' && args[i][wd_len - 1] == '\"') || (args[1][0] == '\'' && args[i][wd_len - 1] == '\''))
