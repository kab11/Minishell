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

void remove_env_var(char **args, t_shell *sh)
{
	int i;
	int j;
	int len;

	i = 1;
	j = -1;
	while (args[i])
	{
		j++;
		len = ft_strlen(args[i]);
		if (ft_strncmp(args[i], sh->arr[j], len) == 0 && sh->arr[j][len] == '=')
		{
			free(sh->arr[j]);
			while (sh->arr[j])
			{
				sh->arr[j] = sh->arr[j + 1];
				j++;
			}
			sh->arr[j] = NULL;
			j = 0;
			i++;
		}
	}
	// get_env_vars(sh, sh->arr);
}

// void remove_env_var(char **args, t_shell *sh)
// {
// 	int i;
// 	char *key;
// 	t_env *head;
// 	t_env *prev;
// 	t_env *lead;
// 	t_env *lag;

// 	head = sh->env_info;

// 	if (head == NULL)
// 		;
// 	else if (head->next == NULL)
// 		free_all_files(head);
// 	else
// 	{
// 		i = 1;
// 		while (args[i] != NULL)
// 		{
// 			lead = head->next;
// 			lag = head;
// 			prev = NULL;
// 			key = ft_strdup(args[i]);
// 			while (lead != NULL && lead->next != NULL)
// 			{	
// 				if (ft_strcmp(lag->key, key) == 0)
// 					break ;
// 				lead = lead->next;
// 				prev = lag;
// 				lag = lag->next;
// 			}
// 			prev->next = lag->next;
// 			free(key);
// 			free_all_files(lag);
// 			i++;
// 		}
// 	}
// }

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
