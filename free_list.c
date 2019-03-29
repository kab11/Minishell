/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:20:58 by kblack            #+#    #+#             */
/*   Updated: 2019/03/27 00:27:44 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
}

void		free_env(char **env)
{
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

void		free_file(t_env *file)
{
	(file->key != NULL) ? free(file->key) : 0;
	(file->value != NULL) ? free(file->value) : 0;
	file->key = NULL;
	file->value = NULL;
	free(file);
	file = NULL;
}

void		free_all_files(t_env *files)
{
	t_env	*temp;

	while (files != NULL)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
}

void		free_struct(t_shell *sh)
{
	(sh->prompt != NULL) ? free(sh->prompt) : 0;
	(sh->pwd != NULL) ? free(sh->pwd) : 0;
	(sh->line != NULL) ? free(sh->line) : 0;
	(sh->env_info != NULL) ? free_all_files(sh->env_info) : 0;
	sh->prompt = NULL;
	sh->pwd = NULL;
	sh->line = NULL;
}
