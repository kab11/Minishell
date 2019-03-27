/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:53:31 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:26:13 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints out the current environment variables when env() is called
*/

int			handle_env(char **args, t_shell *sh)
{
	t_env	*var;

	(void)args;
	var = sh->env_info;
	while (var)
	{
		ft_printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (1);
}
