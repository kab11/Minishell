/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:53:31 by kblack            #+#    #+#             */
/*   Updated: 2019/03/15 16:54:34 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	run a program in a modified environment; -c expansion: changes working DIR 

	environment represents a set of name-value paris that can be used to hold arbitrary 
	information 
	- environment variables are created with setenv()
	- env: runs a program using a modified copy of the shell's environment list;
	  can be sued to add and remove definitions from the list copied from the shell
*/

int handle_env(char **args, t_shell *sh)
{
	t_env *var;

	(void)args;
	var = sh->env_info;
	while (var)
	{
		ft_printf("%s = %s\n", var->key, var->value);
		var = var->next;
	}
	return(1);
}
