/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:20:07 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/06 17:44:08 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

static void	child(char **argv, char **envp, int *fd)
{
	int	file_input;

	file_input = open_file(argv[1], 2);
	if (file_input == -1)
		error(-1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(file_input, STDIN_FILENO);
	close(fd[0]);
	run(argv[2], envp);
}

static void	parent(char **argv, char **envp, int *fd)
{
	int	file_output;

	file_output = open_file(argv[4], 1);
	if (file_output == -1)
		error(-1);
	dup2(fd[0], STDIN_FILENO);
	dup2(file_output, STDOUT_FILENO);
	close(fd[1]);
	run(argv[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid;

	if (argc == 5)
	{
		empty_arg_check(argv, argc);
		if (pipe(fd) == -1)
			error(-1);
		pid = fork();
		if (pid == -1)
			error(-1);
		if (pid == 0)
			child(argv, envp, fd);
		waitpid(pid, NULL, 0);
		parent(argv, envp, fd);
	}
	else
		error(0);
}
