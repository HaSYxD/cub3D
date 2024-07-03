# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afromont <afromont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 01:04:22 by aliaudet          #+#    #+#              #
#    Updated: 2024/07/03 16:49:28 by afromont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
SRC		= src/main.c\
		  src/parsing/parsing.c\
		  src/parsing/texture.c\
		  src/parsing/mappars.c\
		  src/parsing/utilsparsing.c\
		  src/cub3D/map.c\
		  src/cub3D/mouse.c\
		  src/cub3D/player.c\
		  src/cub3D/rendering.c\
		  src/cub3D/color_computing.c\
		  src/cub3D/raycasting.c\
		  src/framework/mlx_context.c\
		  src/framework/inputs.c\
		  src/framework/inputs2.c\
		  src/framework/collision.c\
		  src/framework/drawing/drawing.c\
		  src/framework/drawing/drawing_utils.c\
		  src/framework/math/cub_math.c
OBJS	= $(SRC:.c=.o)

CUB = src/cub3D/cub3d.c
OBJSCUB = $(CUB:.c=.o)

SRC_BONUS = src/cub3D/cub3d_bonus.c\
	    src/framework/monitoring_bonus.c
OBJSBONUS = $(SRC_BONUS:.c=.o)

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
$(NAME): ${OBJS} ${OBJSCUB}
	@cd libs/libft;make
	@cd libs/minilibx-linux;make
	${CC} ${OBJS} ${OBJSCUB} -o ${NAME} ${CFLAGS} ${INCLUDES} ${LIBS}
bonus: ${OBJS} ${OBJSBONUS}
	@cd libs/libft;make bonus
	@cd libs/minilibx-linux;make
	${CC} ${OBJS} ${OBJSBONUS} -o ${NAME} ${CFLAGS} ${INCLUDES} ${LIBS}
%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@
clean:
	@cd libs/libft;make clean
	@if test -d ./libs/minilibx-linux; then\
		cd libs/minilibx-linux;make clean;\
	fi
	${RM} ${OBJS} ${OBJSCUB} ${OBJSBONUS}
fclean: clean
	@cd libs/libft;make fclean
	${RM} ${NAME}
wipe: fclean
	rm -rf ./libs/minilibx-linux
re: fclean all
