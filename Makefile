# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aehrlich <aehrlich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 11:47:51 by pdelanno          #+#    #+#              #
#    Updated: 2023/08/23 11:57:32 by aehrlich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

MLX_PATH = ./mlx/build/

SRCS = 	src/main.c \
		src/parsing/parsing.c \
		src/parsing/parsing_utils.c \
		src/utils/get_next_line.c \
		src/utils/get_next_line_utils.c \
		src/utils/ft_split.c \
		src/raytracing/algebra.c \
		src/raytracing/intersect.c \

OBJS = $(SRCS:.c=.o)

HEADERS = miniRT.h

CFLAGS = #-Wall -Werror -Wextra -g

MLXFLAG = -Iinclude -lglfw -lm

.c.o:
			@cc ${CFLAGS} -c $^ -o $@

all:		$(NAME)

${NAME}:	mlx $(OBJS)
				@cc $(CFLAGS) ${OBJS} -L$(MLX_PATH) -lmlx42 $(MLXFLAG) -o $(NAME)
				@echo "\033[1;5mProgram is ready!\033[0m"
					
mlx:
			@if ! [ -d "./mlx" ]; then \
				git clone https://github.com/codam-coding-college/MLX42.git mlx; \
				cd ./mlx; cmake -B build; cmake --build build -j4; \
			fi

clean:
			@rm -f ${OBJS}
			
reall:
			rm -rf ./mlx
			make re
			
cleanall: fclean
			rm -rf ./mlx

fclean:	clean
			@rm -f ${NAME}
			@echo "\033[1mAll clean!\033[0m"

re: fclean all

.PHONY: all clean fclean re
