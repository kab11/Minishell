/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:34:02 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:34:14 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Removes the first node of the linked list
*/

void		delete_head_node(t_env *head)
{
	t_env	*tmp;

	tmp = NULL;
	if (head->next == NULL)
		return ;
	head->key = head->next->key;
	head->value = head->next->value;
	tmp = head->next;
	head->next = head->next->next;
	return ;
}

/*
** Keeps track of the number of enviroment variables that have been removed
*/

int			number_of_args(char **args)
{
	int		i;
	int		count;

	i = 1;
	count = 0;
	while (args[i++])
		count++;
	return (count);
}

/*
** Removes enviroment variable from linked list
*/

void remove_link(t_env *prev)
{
	t_env	*tmp;

	tmp = prev->next;
	prev->next = prev->next->next;
	free_file(tmp);	
}

/*
** Locates and removes the chosen environment variable from the linked list
*/

void		remove_env_var(char **args, t_shell *sh)
{
	int		i;
	int		count;
	t_env	*head;
	t_env	*prev;
	// t_env	*tmp;

	i = 0;
	head = sh->env_info;
	printf("head = %s\n", head->key);
	while (args[++i])
	{
		if (ft_strcmp(head->key, args[i]) == 0)
			delete_head_node(head);
		prev = head;
		while (prev->next != NULL && ft_strcmp(prev->next->key, args[i]) != 0)
			prev = prev->next;
		if (prev->next == NULL || ft_strcmp(prev->next->key, "_") == 0)
		{
			if ((count = number_of_args(args)) == i)
				return ;
			prev = head;
		}
		else
			remove_link(prev);
	}
}

/*
** Unset removes environment variables from the list of variables that it tracks
*/

int			handle_unsetenv(char **args, t_shell *sh)
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
