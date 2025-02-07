# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgenc <emgenc@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/26 18:50:07 by emgenc            #+#    #+#              #
#    Updated: 2025/02/06 04:09:24 by emgenc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex

SOURCES			= pipex.c utils.c empty_arg_check.c ft_split_quotes.c
OBJECTS			= ${SOURCES:.c=.o}

SOURCES_BONUS	= pipex_bonus.c utils.c empty_arg_check.c get_next_line.c ft_split_quotes.c
OBJECTS_BONUS	= ${SOURCES_BONUS:.c=.o}

CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror

all:	${NAME}

${NAME}:	${OBJECTS}
	@make re -C ./libft-emgenc
	@$(CC) ${OBJECTS} -Llibft-emgenc -lft -o ${NAME}

bonus:	${OBJECTS_BONUS}
	@rm -rf pipex
	@make re -C ./libft-emgenc
	@$(CC) ${OBJECTS_BONUS} -Llibft-emgenc -lft -o ${NAME}

clean:
	@make clean -C ./libft-emgenc
	@rm -rf ${OBJECTS} ${OBJECTS_BONUS}

fclean:	clean
	@make fclean -C ./libft-emgenc
	@rm -rf ${NAME}

re:	fclean all

exec:
	@make fclean && make && make bonus && make clean && clear
	@echo "Pipex: Compilation finished.\nReady!"

.PHONY:	all bonus clean fclean re exec