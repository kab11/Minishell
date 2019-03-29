/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:27:10 by kblack            #+#    #+#             */
/*   Updated: 2019/03/28 21:39:10 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get environment variables and stores them in an array
*/

void		get_str_arr(int n, char **envp, t_shell *sh)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(n * sizeof(char*));
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	tmp[i] = NULL;
	free(sh->arr);
	sh->arr = tmp;
}

/*
** Creates a linked list storing environment
** variables in key=value pairs
*/

void		get_env_vars(t_shell *sh, char **envp)
{
	int		i;
	size_t	sub;
	t_env	*node;
	t_env	*tmp;

	i = -1;
	tmp = NULL;
	while (envp[++i])
	{
		node = new_node();
		sub = ft_strchr(envp[i], '=') - envp[i];
		node->key = ft_strndup(envp[i], sub);
		node->value = ft_strdup(envp[i] + sub + 1);
		if (sh->env_info != NULL)
			tmp->next = node;
		else
			sh->env_info = node;
		tmp = node;
	}
	get_str_arr(i, envp, sh);
	tmp->next = NULL;
}

int			main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_printf("Starting minishell\n");
	ft_bzero(&sh, sizeof(sh));
	get_env_vars(&sh, envp);
	mini_loop(&sh);
	free_struct(&sh);
	return (0);
}
