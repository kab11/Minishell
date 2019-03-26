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

void expansion(char *str, t_shell *sh)
{
	t_env *list;

	list = sh->env_info;
	if (str[0] == '~')
		ft_printf("%s", get_value(sh, "HOME"));
	else if (str[0] == '$')
	{
		str = str + 1;
		ft_printf("%s", get_value(sh, str));
	}
}

void check_args(char *str, t_shell *sh)
{
	(void)sh;
	// printf("str = %s\n", str);
	if (str[0] == '$' || str[0] == '~')
		expansion(str, sh);
	else
		ft_printf("%s", str);
	ft_putchar(' ');
}

int handle_echo(char **args, t_shell *sh)
{
	int i;
	int j;
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '\'')
		{
			j = 0;
			while (args[i][j])
			{
				ft_printf("%c", args[i][j]);
				j++;
			}
		}
		else
			check_args(args[i], sh);
		i++;
	}
	if (i > 1)
		write(1, "\n", 1);
	return (1);
}