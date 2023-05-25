# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 10:54:09 by dinunes-          #+#    #+#              #
#    Updated: 2023/05/05 10:54:09 by dinunes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME	= fractol

# Compiler
CC		= cc
CFLAGS	= -Werror -Wextra -Wall

# Minilibx
MLX_PATH	= mlx_linux/
MLX_NAME	= libmlx.a
MLX			= $(MLX_PATH)$(MLX_NAME)
MLX_SRC     = $(wildcard $(MLX_PATH)*.c)

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
LIBFT_SRC   = $(wildcard $(LIBFT_PATH)*.c)

# Includes
INC			=	-I ./inc/\
				-I ./libft/\
				-I ./minilibx-linux/

# Sources
SRC_PATH	=	src/
SRC			=	main.c \
				init.c	\
				exit.c	\
				hooks.c \
				render.c \
				zoom.c	\
				fractal_sets/mandelbrot.c	\
				fractal_sets/julia.c		\
				fractal_sets/tricorn.c			\
				fractal_sets/celtic.c
SRCS		= $(addprefix $(SRC_PATH), $(SRC))

# Objects
OBJ_PATH	= obj/
OBJ			= $(SRC:.c=.o)
OBJS		= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): | $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	@mkdir $(OBJ_PATH)fractal_sets/

$(MLX): $(MLX_SRC)
	@echo "\033[0;0mMaking \033[0;91mMiniLibX\033[0;0m..."
	@make -sC $(MLX_PATH) > /dev/null 2>&1
	@echo "\033[0;91mMiniLibX \033[0;0mready."

$(LIBFT): $(LIBFT_SRC)
	@echo "Making \033[0;91mlibft\033[0;0m..."
	@make -sC $(LIBFT_PATH) > /dev/null 2>&1
	@echo "\033[0;91mlibft \033[0;0mready."

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	@echo "\033[0;0mCompiling \033[0;91m$(NAME)\033[0;0m..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LIBFT) $(INC) -lXext -lX11 -lm
	@echo "\033[0;91m$(NAME) \033[0;0mready."

bonus: all

clean:
	@echo "\033[0;0mRemoving \033[0;91m.o \033[0;0mobject files..."
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(MLX_PATH) > /dev/null 2>&1
	@make clean -sC $(LIBFT_PATH) > /dev/null 2>&1
	@echo "\033[0;91m.o \033[0;0mobject files removed."

fclean: clean
	@echo "\033[0;mRemoving \033[0;91m$(NAME)\033[0;m..."
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -f $(MLX)
	@echo "\033[0;91m$(NAME) \033[0;0mremoved."

re: fclean all

.PHONY: all re clean fclean
