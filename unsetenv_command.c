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
*/

void delete_head_node(t_env *head)
{
	t_env *tmp;

	if (head->next == NULL)
		return;
	head->key = head->next->key;
	head->value = head->next->value;
	tmp = head->next;
	head->next = head->next->next;
	free(tmp);
	return;
}

void remove_env_var(char **args, t_shell *sh)
{
	int i;
	t_env *head;
	t_env *prev;
	t_env *tmp;

	i = 1;
	head = sh->env_info;
	while (args[i])
	{
		if (ft_strcmp(head->key, args[i]) == 0)
			delete_head_node(head);
		prev = head;
		while (prev->next != NULL && ft_strcmp(prev->next->key, args[i]) != 0)
			prev = prev->next;	
		if (prev->next == NULL || ft_strcmp(prev->next->key, "_") == 0)
			return;
		tmp = prev->next;
		prev->next = prev->next->next;
		free_file(tmp);
		i++;
	}
}

int handle_unsetenv(char **args, t_shell *sh)
{
	if (!args[1])
		ft_printf("unset: not enough arguments\n");
	else
	{
		if (ft_strchr(args[1], '=') == NULL)
			remove_env_var(args, sh);
		else
			ft_printf("unset: %s: invalid parameter name\n", args[1]);
	}
	return (1);
}
