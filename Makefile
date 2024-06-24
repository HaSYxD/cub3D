# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aliaudet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 01:04:22 by aliaudet          #+#    #+#              #
#    Updated: 2024/06/07 01:04:27 by aliaudet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRC		= src/main.c\
		  src/parsing.c\
		  src/cub3D/map.c\
		  src/cub3D/cub3d.c\
		  src/cub3D/player.c\
		  src/cub3D/rendering.c\
		  src/cub3D/raycasting.c\
		  src/editor/editor.c\
		  src/framework/mlx_context.c\
		  src/framework/inputs.c\
		  src/framework/collision.c\
		  src/framework/monitoring.c\
		  src/framework/ui/button.c\
		  src/framework/ui/txt_box.c\
		  src/framework/drawing/drawing.c\
		  src/framework/drawing/draw_line.c\
		  src/framework/drawing/drawing_utils.c\
		  src/framework/math/cub_math.c
OBJS	= $(SRC:.c=.o)
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g -O3
LIBS = -Llibs/libft -lft -Llibs/minilibx-linux -lmlx_Linux -lm -lXext -lX11 -lz
INCLUDES = -I./includes -I./libs/libft -I./libs/minilibx-linux
all: clone ${NAME}
clone:
	@if ! test -d ./libs/minilibx-linux; then\
		cd libs;git clone git@github.com:42Paris/minilibx-linux.git;\
	fi
$(NAME): ${OBJS}
	@cd libs/libft;make
	@cd libs/minilibx-linux;make
	${CC} ${OBJS} -o ${NAME} ${CFLAGS} ${INCLUDES} ${LIBS}
%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
clean:
	@cd libs/libft;make clean
	@if test -d ./libs/minilibx-linux; then\
		cd libs/minilibx-linux;make clean;\
	fi
	${RM} ${OBJS}
fclean: clean
	@cd libs/libft;make fclean
	${RM} ${NAME}
wipe: fclean
	rm -rf ./libs/minilibx-linux
re: fclean all
