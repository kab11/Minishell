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

int handle_echo(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		ft_printf("%s ", args[i]);
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
