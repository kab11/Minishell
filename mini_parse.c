/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 00:01:42 by marvin            #+#    #+#             */
/*   Updated: 2019/03/27 00:31:22 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parses the user's input using space (" ") as a delimiter
*/

char		**parse_user_input(char *line)
{
	char	**arr;
	char	*parsed;
	int		i;

	i = 0;
	if (!(arr = malloc(ft_strlen(line) * sizeof(char*) + 1)))
	{
		ft_printf("malloc failed");
		exit(1);
	}
	line = ft_strtrim(line);
	parsed = ft_strtok(line, ' ');
	while (parsed != NULL)
	{
		arr[i] = parsed;
		i++;
		parsed = ft_strtok(NULL, ' ');
	}
	arr[i] = NULL;
	free(line);
	free(parsed);
	return (arr);
}
