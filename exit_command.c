/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:56:02 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:26:54 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this function causes normal process termination and the value of the status
** is returned to the parent
**
** if the parent is waiting on the child, it is notified of the exit status and
** and the child dies immediately
*/

int	handle_exit(char **args, t_shell *sh)
{
	(void)sh;
	if (args[1])
	{
		if (args[2])
		{
			ft_printf("exit: too many arguments\n");
			return (1);
		}
	}
	return (0);
}
