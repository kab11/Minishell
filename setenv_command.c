/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:33:49 by kblack            #+#    #+#             */
/*   Updated: 2019/03/15 20:33:58 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_setenv(char **args)
{
	int i;

	i = 0;
	printf("YOU'RE IN SETENV!\n");
	while (args[i])
	{
		printf("arg[%d] = %s\n", i, args[i]);
		i++;
	}
	return (1);
}