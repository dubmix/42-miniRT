# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdelanno <pdelanno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 11:47:51 by pdelanno          #+#    #+#              #
#    Updated: 2023/09/13 17:40:13 by pdelanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

MLX_PATH = ./mlx/build/

SRCS = 	src/main.c \
		src/parsing/parsing.c \
		src/parsing/parsing_utils.c \
		src/parsing/parsing_ambient.c \
		src/parsing/parsing_camera.c \
		src/parsing/parsing_light.c \
		src/parsing/parsing_pl.c \
		src/parsing/parsing_sp.c \
		src/parsing/parsing_cy.c \
		src/parsing/parsing_vec.c \
		src/parsing/parsing_color.c \
		src/parsing/parsing_texture.c \
		src/parsing/parsing_error.c \
		src/raytracing/raytracing.c \
		src/raytracing/colors.c \
		src/raytracing/light.c \
		src/raytracing/raytracing_utils.c \
		src/raytracing/camera_check.c \
		src/utils/get_next_line.c \
		src/utils/get_next_line_utils.c \
		src/utils/ft_split.c \
		src/lin_algebra/vector.c \
		src/lin_algebra/vector_utils.c \
		src/lin_algebra/vector_operations.c \
		src/lin_algebra/point.c \
		src/lin_algebra/ray.c \
		src/intersections/cylinder.c \
		src/intersections/cylinder_caps.c \
		src/intersections/cylinder_tube.c \
		src/intersections/sphere.c \
		src/intersections/plane.c \
		src/intersections/intersection_utils.c \
		src/utils/ft_atoi.c \
		src/utils/ft_isdigit.c \
		src/utils/ft_isnumber.c \
		src/utils/ft_stof.c \
		src/utils/ft_strlen.c \
		src/utils/ft_strtrim.c \
		src/utils/ft_strncmp_rev.c \
		src/utils/ft_strncmp.c \
		src/utils/ft_strrchr.c \
		src/utils/ft_lst/ft_lstadd_back.c \
		src/utils/ft_lst/ft_lstadd_front.c \
		src/utils/ft_lst/ft_lstclear.c \
		src/utils/ft_lst/ft_lstdelone.c \
		src/utils/ft_lst/ft_lstiter.c \
		src/utils/ft_lst/ft_lstlast.c \
		src/utils/ft_lst/ft_lstmap.c \
		src/utils/ft_lst/ft_lstnew.c \
		src/utils/ft_lst/ft_lstsize.c

OBJS = $(SRCS:.c=.o)

HEADERS = miniRT.h

CFLAGS = -Wall -Werror -Wextra -g

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
