/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:17:26 by emgenc            #+#    #+#             */
/*   Updated: 2025/02/06 17:47:26 by emgenc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./libft-emgenc/libft.h"
# include <errno.h>
# include <unistd.h>

void	error(int arg);
int		open_file(char *argv, int i);
void	run(char *argv, char **envp);
void	empty_arg_check(char **argv, int argc);
int		is_empty_str(const char *s);
void	accesschecker(char *user_input, char **envp, char **arguments);
char	**ft_split_quotes(const char *s);

#endif