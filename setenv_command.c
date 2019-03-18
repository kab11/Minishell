/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 20:33:49 by kblack            #+#    #+#             */
/*   Updated: 2019/03/15 20:33:58 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	[	int setenv(const char *name, const char *value, int overwrite)	]

	- setenv() function creates a new environment variable by allocating a memory
	  buffer for a string of the form name=value, and copying the strings pointed
	  to by name and value into that buffer 
	- it adds the '=' sign
	- doesn't change the env if the var identified by 'name' already exists and
	  "overwrite" has the value; if "overwrite" is non-zero the env is changed
	- setenv() copies its elements; therefore, the contents of 'name' and 'value'
	  can be modified without affecting the env and you can use auto variables 

	  ** SUCCESS: return 0 FAIL: return -1
*/

int handle_setenv(char **args, t_shell *sh)
{
	int i;
	size_t sub;
	t_env *new;
	t_env *node;

	i = 1;
	new = NULL;
	node = sh->env_info;
	while (node->next != NULL && ft_strcmp(node->key, "_") != 0)
		node = node->next;
	while (args[i])
	{
		new = new_node();
		sub = strchr(args[i], '=') - args[i];
		new->next = new_node();
		new->key = ft_strndup(args[i], sub);
		new->value = ft_strdup(args[i] + sub + 1);
		if (node == NULL)
			node = new;
		else
		{
			node->next = new;
			node = new;
		}
		i++;
	}
	node->next = NULL;
	return (1);
}


// int handle_setenv(char **args, t_shell *sh)
// {
// 	(void)args;
// 	(void)sh;
// 	printf("YOU'RE IN SETENV!\n");
// 	return (1);
// }