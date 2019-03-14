/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:13:54 by kblack            #+#    #+#             */
/*   Updated: 2019/03/14 13:14:03 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		printf("arr[%d]%s\n", i, arr[i]);
		printf("i = %d\n", i);
		i++;
	}
	printf("arr[%d]%s\n", i, arr[i]);
	return (1);
}