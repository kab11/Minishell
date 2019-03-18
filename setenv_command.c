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

/*******
ATM SETENV APPENDS TO THE VERY END OF THE LIST
NEED TO CHANGE TO INSERTING BEFORE THE cur ENV VAR
********/

int handle_setenv(char **args, t_shell *sh)
{
	int i;
	size_t sub;
	t_env *new;
	t_env *prev;
	t_env *cur;

	i = 1;
	cur = sh->env_info;
	if (args[i])
	{
		if (ft_strchr(args[i], '=') == NULL)
			return (1);
		while (cur->next != NULL && ft_strcmp(cur->key, "_") != 0)
		{
			prev = cur;
			cur = cur->next;
		}
		while (args[i])
		{
			new = new_node();
			sub = ft_strchr(args[i], '=') - args[i];
			new->key = ft_strndup(args[i], sub);
			new->value = ft_strdup(args[i] + sub + 1);
			if (cur == NULL)
				cur = new;  
			else
			{
				new->next = cur;
				prev->next = new;
				prev = new;
			}
			i++;
		}
		cur->next = NULL;
	}
	else
		handle_env(args, sh);
	return (1);
}
