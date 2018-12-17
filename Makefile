# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/09/14 01:26:20 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

GC = gcc -O3 -Ipthreads -Wall -Wextra -Werror
CM = cmake -O3 -Ipthreads -Wall -Wextra -Werror
CL = clang -O3 -Ipthreads -Wall -Wextra -Werror

[[ $1 = "clang" ]] && CC=CL || CC=GC
[[ $1 = "cmake" ]] && CC=CM || CC=GC

LIBKEY = -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

SRC_N =	main.c \
		draw.c \
		keys.c \
		init.c \
		hooks.c \
		color.c \
		ram_man.c \
		fractals.c \
		interface.c \
		init_fract.c

SRC = $(addprefix src/, $(SRC_N))

OBJ = $(SRC:.c=.o)

LIBS = libft/libft.a

all: $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME): liball $(OBJ)
	$(CC) $(LIBKEY) $(OBJ) $(LIBS) -o $(NAME)

clean: libclean
	rm -f $(OBJ)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

clang: $(NAME)

cmake: $(NAME)

liball:
	@make -C libft/ all

libclean:
	@make -C libft/ clean

libfclean:
	@make -C libft/ fclean

libre:
	@make -C libft/ re
