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

void	free_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

void		free_file(t_env *file)
{
	(file->key != NULL) ? free(file->key) : 0;
	(file->value != NULL) ? free(file->value) : 0;
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

void free_struct(t_shell *sh)
{
	(sh->display != NULL) ? free(sh->display) : 0;
	(sh->prompt != NULL) ? free(sh->prompt) : 0;
	(sh->arr != NULL) ? free_env(sh->arr) : 0;
	(sh->pwd != NULL) ? free(sh->pwd) : 0;
	(sh->line != NULL) ? free(sh->line) : 0;
}
