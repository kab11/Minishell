/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:41:09 by kblack            #+#    #+#             */
/*   Updated: 2019/03/28 21:38:05 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Gets location of current directory to display the prompt
*/

void		set_pwd(t_shell *sh)
{
	char	*curr;
	char	*str;

	sh->prompt != NULL ? free(sh->prompt) : 0;
	sh->prompt = NULL;
	curr = ft_strnew(PATH_MAX);
	getcwd(curr, PATH_MAX);
	str = ft_strrchr(curr, '/') + 1;
	sh->prompt = ft_strdup(str);
	free(curr);
	curr = NULL;
}

/*
** runs command loop
*/

void		mini_loop(t_shell *sh)
{
	int		status;
	char	**args;

	status = 1;
	while (status)
	{
		set_pwd(sh);
		ft_printf(BOLDCYAN "🍻  %s 🍻 " RESET, sh->prompt);
		ft_printf(BOLDRED " >> " RESET);
		sh->line != NULL ? free(sh->line) : 0;
		sh->line = NULL;
		get_next_line(1, &sh->line);
		if (ft_strcmp(sh->line, "") == 0)
			continue;
		args = ft_strsplit(sh->line, ' ');
		if (ft_strcmp(args[0], "$"))
		{
			expansion(args[0], sh);
			ft_printf("\n");
			continue;
		}
		status = execute(args, sh);
		free_env(args);
	}
}
