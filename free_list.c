/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 22:20:58 by kblack            #+#    #+#             */
/*   Updated: 2019/03/17 22:21:08 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file(t_env *file)
{
	(file->key != NULL) ? free(file->key) : 0;
	(file->value != NULL) ? free(file->value) : 0;
	free(file);
	file = NULL;
}

void	free_all_files(t_env *files)
{
	t_env	*temp;

	while (files != NULL)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
}
