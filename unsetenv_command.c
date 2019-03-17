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

int handle_unsetenv(char **args)
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