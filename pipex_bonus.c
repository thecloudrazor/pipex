/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:20:09 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/06 17:45:21 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>

static void	child(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error(-1);
	pid = fork();
	if (pid == -1)
		error(-1);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		run(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

static void	exec_heredoc(char *line, char *limiter, int fd[])
{
	close(fd[0]);
	line = get_next_line(STDIN_FILENO, 0);
	while (line != NULL)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			get_next_line(STDIN_FILENO, -1);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO, 0);
	}
	get_next_line(STDIN_FILENO, -1);
	exit(EXIT_SUCCESS);
}

static void	here_doc(char *limiter, int argc)
{
	int		fd[2];
	char	*line;

	if (argc < 6)
		error(1);
	if (pipe(fd) == -1)
		error(-1);
	line = NULL;
	if (fork() == 0)
		exec_heredoc(line, limiter, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

static void	bonus_main_handler(int argc, char **argv, int **files)
{
	int	*fo;
	int	*fi;
	int	*i;

	fo = files[0];
	fi = files[1];
	i = files[2];
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		*i = 3;
		*fo = open_file(argv[argc - 1], 0);
		here_doc(argv[2], argc);
	}
	else
	{
		*i = 2;
		*fo = open_file(argv[argc - 1], 1);
		*fi = open_file(argv[1], 2);
		dup2(*fi, STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	file_input;
	int	file_output;
	int	*files[3];

	files[0] = &file_output;
	files[1] = &file_input;
	files[2] = &i;
	if (argc >= 5)
	{
		empty_arg_check(argv, argc);
		bonus_main_handler(argc, argv, files);
		while (i < argc - 2)
			child(argv[i++], envp);
		dup2(file_output, STDOUT_FILENO);
		run(argv[argc - 2], envp);
	}
	else
		error(1);
}
