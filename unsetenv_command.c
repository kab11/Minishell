/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:34:02 by kblack            #+#    #+#             */
/*   Updated: 2019/03/15 20:34:11 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	[	int unsetenv(const char *name)	]
	unsetenv function removes the variable identified by 'name' from the env 
	- 'name' should not include '=' sign
	- 


	** SUCCESS: return 0 FAIL: return -1
*/

int handle_unsetenv(char **args, t_shell *sh)
{
	int i;

	i = 0;
	printf("YOU'RE IN UNSETENV!\n");
	while (args[i])
	{
		printf("arg[%d] = %s\n", i, args[i]);
		i++;
	}
	return (1);
}