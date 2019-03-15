/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:09:29 by kblack            #+#    #+#             */
/*   Updated: 2019/03/13 14:12:05 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <dirent.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"
# include <string.h>

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define BOLDCYAN			"\033[1m\033[36m"
# define RESET				"\x1b[0m"
# define BACK_YELL			"\x1b[47m"

// enum e_type
// {
	
// };

char **parse_user_input(char *line);
int execute(char **arr);


#endif
