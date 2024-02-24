BLUE = \033[0;94m
GREEN = \e[1;92m
RED = \033[0;91m
RESET = \033[1;30m
WHITE = \033[1;97m
YELLOW = \033[1;33m

EMOJI_PACKAGE = \360\237\223\246
EMOJI_HAMMER = \360\237\224\250
EMOJI_TRASH = \360\237\227\221\357\270\217

NAME = fractol

CC = cc
CFLAGS = -Werror -Wextra -Wall -O3

MINILIBX_PATH = minilibx-linux/
MINILIBX_NAME = libmlx.a
MINILIBX = $(MINILIBX_PATH)$(MINILIBX_NAME)

LIBFT_PATH = lib/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

INC = -I ./inc/
SRC_PATH = src/
OBJ_PATH = obj/

SRC = $(addprefix $(SRC_PATH), \
		main.c \
				init.c	\
				exit.c	\
				hooks.c \
				render.c \
				zoom.c	\
				fractal_sets/mandelbrot.c	\
				fractal_sets/julia.c		\
				fractal_sets/tricorn.c			\
				fractal_sets/celtic.c)

$(OBJ): $(OBJ_PATH)

OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "$(EMOJI_HAMMER)	$(BLUE)Compiling $(WHITE)$(NAME)		$(BLUE)%-33s$(WHITE)\r" $(notdir $@)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/fractal_sets

$(LIBFT):
	@make -sC $(LIBFT_PATH) > /dev/null

$(MINILIBX):
	@make -sC $(MINILIBX_PATH) > /dev/null

$(NAME): $(MINILIBX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -L$(MINILIBX_PATH) -lmlx -L/usr/X11/lib -lX11 -lXext -lm
	@printf  "\n$(EMOJI_PACKAGE)	$(WHITE)$(NAME)			$(YELLOW)compiled$(WHITE)\n"

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH) > /dev/null
	@make clean -sC $(MINILIBX_PATH) > /dev/null

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@rm -f $(MINILIBX)
	@printf "$(EMOJI_TRASH)	$(WHITE)$(NAME)			$(RED)removed$(WHITE)\n"

re: fclean all

.PHONY: all re clean fclean run