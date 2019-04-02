/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:41:09 by kblack            #+#    #+#             */
/*   Updated: 2019/03/29 15:47:29 by kblack           ###   ########.fr       */
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
	char	*trim;

	status = 1;
	while (status)
	{
		set_pwd(sh);
		ft_printf(BOLDCYAN "🍻  %s 🍻 " RESET, sh->prompt);
		ft_printf(BOLDRED " >> " RESET);
		sh->line != NULL ? free(sh->line) : 0;
		sh->line = NULL;
		get_next_line(1, &sh->line);
		trim = ft_strtrim(sh->line);
		if (ft_strcmp(trim, "") == 0)
		{
			free(trim);
			continue;
		}
		args = ft_strsplit(trim, ' ');
		status = execute(args, sh);
		free(trim);
		free_env(args);
	}
}
