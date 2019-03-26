/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 00:01:42 by marvin            #+#    #+#             */
/*   Updated: 2019/03/22 00:01:46 by marvin           ###   ########.fr       */
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
	char *parsed;
	int i;

	i = 0;
	if (!(arr = malloc(ft_strlen(line) * sizeof(char*) + 1)))
	{
		ft_printf("malloc failed");
		exit(1);
	}
	parsed = strtok(line, " ");
	while (ft_isspace(*parsed))
		parsed++;
	while (parsed != NULL)
	{
		arr[i] = parsed;
		i++;
		parsed = strtok(NULL, " ");;
	}
	arr[i] = NULL;
	return (arr);
}

// if ((start = ft_strstr(line, "echo")) && (ft_strchr(line, '\'') || ft_strchr(line, '\"')))
	// {
	// 	arr[i] = ft_strdup(line);
	// 	i++;
	// 	arr[i] = NULL;
	// }
	// else
