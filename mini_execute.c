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
	 - most commands a shell executes are programs, but others are built right into the shell
	 - a shell builtin is a command/function called from a chell that is executed directly in
	   the shell itself, instead of an external executable program which the shell would load 
	   and execute

	** int execve(const char* pathname, char* const argv[], char *const envp[]) **
	 - the 'filename' is sought in the list of directories specified in the PATH environment
	   variable 
*/

/*
	int execve(const char* pathname, char* const argv[], char *const envp[])
	-	pathname: pathname of the new program to be loaded into the process's memory
	-	argv: specifies the CL args to be passed to the new program; argv[0] is the
		command name 
	-	envp: specifies the environment list for the new program; name=value 
	-	the only time execve returns is upon error 
	~ replaces the current running program with an entirely new one 

	1) the 1st arg is the name of the command
	2) the 2nd arg is the name of the command and the args passed to the command itself;
		must be NULL terminated

	getpid(): returns the current process id

	waitpid(): takes PID of process program is waiting on, a variable, options flag 
*/

/*
	1) start with basic function that we will be pointing to
	2) define a pointer to a function
	3) point to the function; passing the pointer to another function is that same thing
*/

/*
	execve(): loads a new program into a process's memory
	envp: specfies the environment list for the new program 
	getcwd(): places a NULL terminated string containing the absolute pathname of the current
			  woring directory into the allocated buffer pointed to by cwdbuf 
*/

/*
	1) Get path name for arr[0]
*/

struct s_dispatch builtins[BUILTIN_COUNT] = {
	{"cd", handle_cd},
	{"env", handle_env},
	{"echo", handle_echo},
	{"exit", handle_exit},
	{"setenv", handle_setenv},
	{"unset", handle_unsetenv}
};


char *find_path(char *cmd, t_shell *sh)
{
	t_env *list;
	char **p;
	char *tmp;
	char *path;
	int i;

	i = -1;
	p = NULL;
	list = sh->env_info;
	while (list)
	{
		if (ft_strcmp(list->key, "PATH") == 0)
		{
			p = ft_strsplit(list->value, ':');
			break ;
		}
		list = list->next;
	}
	while (p[++i])
	{
		tmp = ft_strjoin(p[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (NULL);
}
/* create a char ** to a array of string to pass in execve() */
int launch(char **arr, t_shell *sh)
{
	int status;
	char *path;
	pid_t childPID;
	pid_t wait_ret;

	(void)sh;
	childPID = fork();
	if (childPID < 0)
	{
		ft_printf("PID error\n");
		exit(1);
	}
	if (childPID == 0) /* Child */
	{
		ft_printf("Child created\n");

		path = find_path(arr[0], sh);
		execve(path, arr, sh->arr);
		ft_printf("Child = %d\t Parent = %d\n", getpid(), getppid());
	}
	else /* Parent */
	{
		wait_ret = waitpid(childPID, &status, 0);
		ft_printf("Child killed\n");
		ft_printf("Parent = %d\t Child = %d\n", getpid(), childPID);
	}
	free(arr);
	return (1);
}

int execute(char **arr, t_shell *sh)
{
	int i;

	i = 0;
	if (arr[0] == NULL)
		return (1);
	while (i < BUILTIN_COUNT)
	{
		if (ft_strcmp(arr[0], builtins[i].key) == 0)
			return(builtins[i].fxnptr(arr, sh));
		i++;
	}
	return (launch(arr, sh));
}

