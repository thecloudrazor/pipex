/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:20:02 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/06 17:44:02 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <string.h>

void	error(int arg)
{
	if (arg == 1)
	{
		ft_putstr_fd("Error! You have parsed bad/wrong arguments.\n", 2);
		ft_putstr_fd("./pipex <file1> <cmd1> <...> <file2>\n", 1);
		ft_putstr_fd("./pipex \"here_doc\" <LIMITER> <cmd1> <...> <file>\n", 1);
	}
	else if (arg == 0)
	{
		ft_putstr_fd("Error! You have parsed bad/wrong arguments.\n", 2);
		ft_putstr_fd("./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	else
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	exit(EXIT_FAILURE);
}

static void	iterative_free(char **paths)
{
	int	j;

	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	if (!cmd)
		return (NULL);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (iterative_free(paths), path);
		free(path);
		i++;
	}
	return (iterative_free(paths), NULL);
}

void	run(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	if (!argv || is_empty_str(argv))
		exit(EXIT_SUCCESS);
	cmd = ft_split_quotes(argv);
	accesschecker(cmd[0], envp, cmd);
	path = find_path(cmd[0], envp);
	if (!path)
	{
		iterative_free(cmd);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": command not found", 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
		error(-1);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error(-1);
	return (file);
}
