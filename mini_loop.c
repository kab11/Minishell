/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:41:09 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:21:07 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** reads a line from stdin using get_next_line()
*/

char		*get_info(void)
{
	char	*line;

	if (get_next_line(0, &line) == 1)
		return (line);
	return (NULL);
}

/*
** stores current location and displays the shell prompt
*/

void		set_pwd(t_shell *sh)
{
	char	*curr;
	char	*str;

	free(sh->prompt);
	curr = ft_strnew(PATH_MAX);
	getcwd(curr, PATH_MAX);
	str = ft_strrchr(curr, '/') + 1;
	sh->prompt = ft_strdup(str);
	free(curr);
}

/*
** runs command loop
*/

void		mini_loop(t_shell *sh)
{
	int		status;
	char	*line;
	char	**args;

	status = 1;
	while (status)
	{
		set_pwd(sh);
		ft_printf(BOLDCYAN "🍻  %s 🍻 " RESET, sh->prompt);
		ft_printf(BOLDRED " >> " RESET);
		line = get_info();
		sh->line = ft_strdup(line);
		if (ft_strcmp(line, "") == 0)
			continue;
		args = parse_user_input(line);
		status = execute(args, sh);
		free(line);
	}
	free_env(args);
}
