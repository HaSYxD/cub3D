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
		  src/drawing/drawing.c\
		  src/drawing/drawing_utils.c\
		  src/math/cub_math.c
OBJS	= $(SRC:.c=.o)
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra -g
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
	${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -c $< -o $@
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
