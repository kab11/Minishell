/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:27:10 by kblack            #+#    #+#             */
/*   Updated: 2019/03/18 23:24:07 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	BUILTINS:
	echo			ch 			setenv		pwd		
	unsetenv		env 		exit

	EXPANSIONS:
	$				~
*/

/*
	SIGNALS
	-	ctrl-c = SIGINT ==> causes the program to exit 
	-	ctrl-z = SIGTSTP ==> stops the current runnning process 
	-	signal handler is a pre-defined function which is invoked when the signal is received 
*/

/*
	fork(): allows one process, the parent prcoess, to create a new process, the child
	the new child pocesses an (almost) exact duplicate of the parent; the child get a copy of the parent's
	stack, data, heap, and text segments 
	-	e.g. A network server process may listen for incoming clinet requests and create a new child process
		to handle each request; meanwhile, the server process continues to listen for further client connections
	-	with fork() now 2 processes exist bu the have seperate copies of the stack, data, and heap segments 
	-	after using fork() there isn't a way to tell which of the 2 processes is next in the CPU; this can lead
		to errors called "race conditions"
	-	implements "copy-on-write": initially fork() sets up things so that the page-table entries refer to the
		same physical memory and the pages are marked as 'read-only'

	exit(status): terminates a process, making all resources avaiable for reallocation by the kernel;
	the status arg is an integer that determines the termination statu for the process; using wait() system
	call, the parent can retrieve this status

	wait(&status): 1) if child hasn't been terminated by exit(), wait() suspends execution of the process until
	one of its children has been terminated; 2) the termination status of the child is returned in the status
	argumnet of wait()
	-	wait(&): causes the process to run in the background 

	execve(pathname, argv, envp): loads a new program into a process's memory
*/

// struct stat {
//     dev_t     st_dev;     /* ID of device containing file */
//     ino_t     st_ino;     /* inode number */
//     mode_t    st_mode;    /* protection */
//     nlink_t   st_nlink;   /* number of hard links */
//     uid_t     st_uid;     /* user ID of owner */
//     gid_t     st_gid;     /* group ID of owner */
//     dev_t     st_rdev;    /* device ID (if special file) 
//     off_t     st_size;    /* total size, in bytes */
//     blksize_t st_blksize; /* blocksize for file system I/O */
//     blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
//     time_t    st_atime;   /* time of last access */
//     time_t    st_mtime;   /* time of last modification */
//     time_t    st_ctime;   /* time of last status change */
// };

// struct rusage {
//     struct timeval ru_utime; /* user CPU time used */
//     struct timeval ru_stime; /* system CPU time used */
//     long   ru_maxrss;        /* maximum resident set size */
//     long   ru_ixrss;         /* integral shared memory size */
//     long   ru_idrss;         /* integral unshared data size */
//     long   ru_isrss;         /* integral unshared stack size */
//     long   ru_minflt;        /* page reclaims (soft page faults) */
//     long   ru_majflt;        /* page faults (hard page faults) 
//     long   ru_nswap;         /* swaps */
//     long   ru_inblock;       /* block input operations */
//     long   ru_oublock;       /* block output operations */
//     long   ru_msgsnd;        /* IPC messages sent */
//     long   ru_msgrcv;        /* IPC messages received */
//     long   ru_nsignals;      /* signals received */
//     long   ru_nvcsw;         /* voluntary context switches */
//     long   ru_nivcsw;        /* involuntary context switches */
// };

/*
** reads a line from stdin using get_next_line()
*/

t_env	*new_node(void)
{
	t_env	*new_node;

	new_node = (t_env*)malloc(sizeof(t_env));
	ft_bzero(new_node, sizeof(t_env));
	return (new_node);
}

char *get_info()
{
	char *line;
	char **arr;

	arr = (char**)malloc(sizeof(char*));
	if (get_next_line(0, &line) == 1)
			return (line);
	return (NULL);
}

void mini_loop(t_shell *sh)
{
	int status;
	char *line;
	char **args;

	status = 1;
	sh->display = "$>";
	while (status)
	{
		ft_printf(BOLDCYAN "%s " RESET, sh->display);
		line = get_info();
		if (ft_strcmp(line, "") == 0)
			continue;
		args = parse_user_input(line);
		status = execute(args, sh);
	}
}

/*
** Get environment variables and stores them structure
** of key-value pairs
*/

void get_str_arr(int n, char **envp, t_shell *sh)
{
	char **tmp;
	int i;

	i = 0;
	tmp = malloc(n * sizeof(char*));
	while (envp[i])
	{
		tmp[i] = ft_strdup(envp[i]);
		i++;
	}
	sh->arr = tmp;
}

void get_env_vars(t_shell *sh, char **envp)
{
	int i; 
	size_t sub;
	t_env *node;
	t_env *tmp;

	i = 0;
	node = NULL;
	tmp = NULL;
	while (envp[i])
	{
		node = new_node();
		sub = strchr(envp[i], '=') - envp[i];
		node->next = new_node();
		node->key = ft_strndup(envp[i], sub);
		node->value = ft_strdup(envp[i] + sub + 1);
		if (sh->env_info != NULL)
		{
			tmp->next = node;
			tmp = node;
		}
		else
			sh->env_info = tmp = node;
		i++;
	}
	get_str_arr(i, envp, sh);
	tmp->next = NULL;
}

/*
** Reads, Parses, and Executes the shell
*/

int main(int argc, char **argv, char **envp)
{
	ft_printf("Starting minishell\n");
	t_shell sh;

	(void)argc;
	(void)argv;
	ft_bzero(&sh, sizeof(sh));
	get_env_vars(&sh, envp);
	mini_loop(&sh);
	return (0);
}
