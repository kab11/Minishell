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

/*
** 1) Check if more than 1 argument
**		- if not then call env
** 2) Check if new env already exists
**		- if so replace with new value
**		- if not iterate to the end of the list and add new env var 
** 3) return (1)
*/

/*
** Unhandled use case:
** quotes ==> "" and ''
*/

void add_new_env_var(t_env *prev, t_env *cur, char *env_var, char *val)
{
	t_env *new;

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

void check_env_var_exists(char **args, t_shell *sh)
{
	int i;
	size_t sub;
	char *key;
	char *val;
	t_env *cur;
	t_env *prev;

	i = 1;
	while (args[i])
	{

		while (args[i] != NULL && ft_strchr(args[i], '=') == NULL)
			i++;
		if (args[i] == NULL)
			break; 
		cur = sh->env_info;
		sub = ft_strchr(args[i], '=') - args[i];
		key = ft_strndup(args[i], sub);
		val = ft_strdup(args[i] + sub + 1);
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
		free(key);
		free(val);
		i++;
	}
}


int handle_setenv(char **args, t_shell *sh)
{
	if (!args[1])
		handle_env(args, sh);
	else
		check_env_var_exists(args, sh);
	return (1);
}
























