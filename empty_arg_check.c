/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_arg_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:26:15 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/06 17:43:48 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

static void	emptyargumenterror(void)
{
	ft_putstr_fd("bash: syntax error near unexpected token `|'", 2);
	ft_putstr_fd("\n", 2);
	exit(258);
}

void	accesschecker(char *user_input, char **envp, char **arguments)
{
	char	*skipper;

	skipper = user_input;
	while (*skipper == ' ' || *skipper == '\t')
		skipper++;
	if (*skipper == '/')
	{
		if (access(skipper, F_OK) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(strerror(ENOENT), 2);
			ft_putstr_fd("\n", 2);
			exit(127);
		}
		if (access(skipper, X_OK) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(strerror(EACCES), 2);
			ft_putstr_fd("\n", 2);
			exit(126);
		}
		if (execve(skipper, arguments, envp) == -1)
			error(-1);
	}
}

int	is_empty_str(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	empty_arg_check(char **argv, int argc)
{
	int	i;

	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (is_empty_str(argv[2]))
			emptyargumenterror();
		i = 4;
	}
	else
		i = 3;
	while (i < argc - 2)
	{
		if (is_empty_str(argv[i]))
			emptyargumenterror();
		i++;
	}
}
