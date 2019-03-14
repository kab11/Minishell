/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 11:47:35 by kblack            #+#    #+#             */
/*   Updated: 2019/03/14 11:47:44 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** parses the user's input using ' ' as a delimiter; need to account for if
** echo and using '' or "" quotes
*/

char **parse_user_input(char *line)
{
	char **arr;

	arr = (char**)malloc(ft_strlen(line) * sizeof(char*));
	arr = ft_strsplit(line, ' ');
	return (arr);
}

// if ((start = ft_strstr(line, "echo")) && (ft_strchr(line, '\'') || ft_strchr(line, '\"')))
	// {
	// 	arr[i] = ft_strdup(line);
	// 	i++;
	// 	arr[i] = NULL;
	// }
	// else
