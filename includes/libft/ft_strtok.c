/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 12:57:16 by kblack            #+#    #+#             */
/*   Updated: 2019/03/21 12:57:21 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char *sep)
{
	static char	*stock;
	char		*ptr;
	int			i;

	i = 0;
	ptr = NULL;
	stock = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (i == 0 && ft_strcmp(stock, sep) != 0)
		{
			i = 1;
			ptr = stock;
		}
		else if (i == 1 && ft_strcmp(stock, sep) == 0)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock++;
	}
	// free (stock);
	return (ptr);
}
