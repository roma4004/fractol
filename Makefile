# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dromanic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/24 18:20:17 by dromanic          #+#    #+#              #
#    Updated: 2018/12/25 19:15:16 by dromanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

GC = gcc -O3 -Ipthreads -Wall -Wextra -Werror
CM = cmake -O3 -Ipthreads -Wall -Wextra -Werror
CL = clang -O3 -Ipthreads -Wall -Wextra -Werror

[[ $1 = "clang" ]] && CC=CL || CC=GC
[[ $1 = "cmake" ]] && CC=CM || CC=GC

LIBKEY = -L ./libraries/minilibx -lmlx \
		 -framework OpenGL \
		 -framework AppKit

OBJ_PATH   = objectives
SRC_PATH   = sources
LIBS_PATH  = libraries
LIBFT_PATH = ${LIBS_PATH}/libft
MLX_PATH   = ${LIBS_PATH}/minilibx

INC = -I ${MLX_PATH}/ -I ${LIBFT_PATH}/ -I includes/

SRC_N = main.c \
		draw.c \
		keys.c \
		init.c \
		hooks.c \
		color.c \
		ram_man.c \
		fractals.c \
		interface.c \
		init_fract.c

SRC = $(addprefix ${SRC_PATH}/, $(SRC_N))

OBJ = $(addprefix ./$(OBJ_PATH)/, $(SRC_N:.c=.o))

LIBS = ${LIBFT_PATH}/libft.a

all: $(NAME)

./$(OBJ_PATH)/%.o : ./$(SRC_PATH)/%.c
	$(CC) $(INC) -c $< -o $@

$(NAME): objdir liball $(OBJ)
	$(CC) $(LIBKEY) $(OBJ) $(LIBS) -o $(NAME)

objdir:
	mkdir -p $(OBJ_PATH)

clean: libclean
	rm -rf $(OBJ_PATH)

fclean: clean libfclean
	rm -f $(NAME)

re: fclean all

clang: $(NAME)

cmake: $(NAME)

liball:
	@make -C ${LIBFT_PATH}/ all

libclean:
	@make -C ${LIBFT_PATH}/ clean

libfclean:
	@make -C ${LIBFT_PATH}/ fclean

libre:
	@make -C ${LIBFT_PATH}/ re

norm:
	norminette $(LIBFT_PATH)/*.c
	norminette $(LIBFT_PATH)/*.h
	norminette $(SRC_PATH)/*.c
	norminette $(INC_PATH)/*.h

normf:
	@norminette $(NORMFLAGS) $(LIBFT_PATH)/*.c  | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) $(LIBFT_PATH)/*.h  | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) $(SRC_PATH)/*.c  | grep -E '^(Error|Warning)'
	@norminette $(NORMFLAGS) $(INC_PATH)/*.h  | grep -E '^(Error|Warning)'

.phony: all clean fclean re