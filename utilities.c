/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:45:44 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:35:31 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*new_node(void)
{
	t_env	*new_node;

	new_node = (t_env*)malloc(sizeof(t_env));
	ft_bzero(new_node, sizeof(t_env));
	return (new_node);
}

void		expansion(char *str, t_shell *sh)
{
	t_env	*list;

	list = sh->env_info;
	if (str[0] == '~')
		ft_printf("%s", get_value(sh, "HOME"));
	else if (str[0] == '$')
	{
		str = str + 1;
		ft_printf("%s", get_value(sh, str));
	}
}

void		check_args(char *str, t_shell *sh)
{
	if (str[0] == '$' || str[0] == '~')
		expansion(str, sh);
	else
		ft_printf("%s", str);
	ft_putchar(' ');
}

int			check_dir(char *name)
{
	DIR		*d_stream;

	d_stream = opendir(name);
	if (d_stream == NULL)
		return (-1);
	closedir(d_stream);
	d_stream = NULL;
	return (0);
}

char		*get_value(t_shell *sh, char *name)
{
	t_env	*tmp;

	tmp = sh->env_info;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
