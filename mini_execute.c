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

/*
	int execve(const char* pathname, char* const argv[], char *const envp[])
	-	pathname: pathname of the new program to be loaded into the process's memory
	-	argv: specifies the CL args to be passed to the new program; argv[0] is the
		command name 
	-	envp: specifies the environment list for the new program; name=value 
	-	the only time execve returns is upon error 

	1) the 1st arg is the name of the command
	2) the 2nd arg is the name of the command and the args passed to the command itself;
		must be NULL terminated*/



int execute(char **arr)
{
	int i;
	int status;
	pid_t childPID;


	i = 0;
	childPID = fork();
	if (childPID < 0)
	{
		ft_printf("PID error\n");
		exit(1);
	}
	if (childPID > 0)
	{
		wait(&status);
		// ft_printf("Parent = %d\t Child = %d\n", getpid(), childPID);
	}
	else	/* never returns if the call is successful */
	{
		if (execve(arr[0], arr, NULL) < 0 )
		{
			ft_printf("zsh: command not found : %s\n", arr[0]);
			exit(1);
		}
		// ft_printf("Child = %d\t Parent = %d\n", getpid(), getppid());
	}
	free(arr);
	return (1);
}