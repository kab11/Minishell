/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:33:49 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:32:33 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Setenv creates a new environment variable and adds to the list of tracked
** environment variables if it doesn't already exist. If it does already exist
** it updates the environment variable information
*/

void		add_new_env_var(t_env *prev, t_env *cur, char *env_var, char *val)
{
	t_env	*new;

	new = new_node();
	new->key = ft_strdup(env_var);
	new->value = ft_strdup(val);
	if (cur == NULL)
		cur = new;
	else
	{
		new->next = cur;
		prev->next = new;
		prev = new;
	}
	cur->next = NULL;
}

void search_list(t_env *cur, char *key, char *val)
{
	t_env	*prev;

	while (cur->next != NULL)
	{
		prev = cur;
		if (ft_strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = ft_strdup(val);
			break ;
		}
		cur = cur->next;
	}
	if (cur == NULL || cur->next == NULL)
		add_new_env_var(prev, cur, key, val);
}

void		check_env_var_exists(char **args, t_shell *sh)
{
	int		i;
	size_t	sub;
	char	*key;
	char	*val;
	t_env	*cur;

	i = 1;
	while (args[i])
	{
		while (args[i] != NULL && ft_strchr(args[i], '=') == NULL)
			i++;
		if (args[i] == NULL)
			break ;
		cur = sh->env_info;
		sub = ft_strchr(args[i], '=') - args[i];
		key = ft_strndup(args[i], sub);
		val = ft_strdup(args[i] + sub + 1);
		search_list(cur, key, val);
		free(key);
		free(val);
		i++;
	}
}

int			handle_setenv(char **args, t_shell *sh)
{
	if (!args[1])
		handle_env(args, sh);
	else
		check_env_var_exists(args, sh);
	return (1);
}
