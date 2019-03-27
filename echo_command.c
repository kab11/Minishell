/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:38:36 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:25:43 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** handles echo followed by a single quoted string
*/

void		single_quote(char *str)
{
	int		i;
	char	**s;

	i = 0;
	s = NULL;
	s = ft_strsplit(str, '\'');
	while (s[++i])
		ft_printf("%s", s[i]);
	free_env(s);
}

/*
** handles echo followed by a double quoted string
*/

void		double_quote(char *s, t_shell *sh, char *path)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != '$')
		{
			ft_printf("%c", s[i]);
			i++;
		}
		else
		{
			while (!ft_isspace(s[i]) && s[i])
			{
				path[k] = s[i];
				k++;
				i++;
			}
			expansion(path, sh);
		}
	}
}

void		quote_handler(char *str, t_shell *sh)
{
	char	**s;
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = ft_strnew(sizeof(char));
	s = ft_strsplit(str, '\"');
	while (s[++i])
		double_quote(s[i], sh, path);
	free_env(s);
	free(path);
}

/*
** builtin function implementation of echo
*/

int			handle_echo(char **args, t_shell *sh)
{
	int		i;

	i = 0;
	if (ft_strchr(sh->line, '\'') || ft_strchr(sh->line, '\"'))
	{
		if (ft_strchr(sh->line, '\''))
			single_quote(sh->line);
		else if (ft_strchr(sh->line, '\"'))
			quote_handler(sh->line, sh);
		write(1, "\n", 1);
	}
	else
	{
		while (args[++i])
			check_args(args[i], sh);
	}
	if (i > 1)
		write(1, "\n", 1);
	return (1);
}
