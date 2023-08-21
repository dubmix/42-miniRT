# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdelanno <pdelanno@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 11:47:51 by pdelanno          #+#    #+#              #
#    Updated: 2023/08/21 11:57:09 by pdelanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = src/main.c

OBJS = $(SRCS:.c=.o)

HEADERS = miniRT.h

CFLAGS = -Wall -Werror -Wextra -g

.c.o:
			@cc ${CFLAGS} -c $^ -o $@

all:		$(NAME)

${NAME}:	$(OBJS)
					@cc ${OBJS} $(CFLAGS) -o $(NAME)
					@echo "\033[1;5mProgram is ready!\033[0m"

clean:
			@rm -f ${OBJS}

fclean:
			@cd src && rm -f ${NAME}
			@rm -f ${NAME}
			@echo "\033[1mAll clean!\033[0m"

re: fclean all

.PHONY: all clean fclean re
