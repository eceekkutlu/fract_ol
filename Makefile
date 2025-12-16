NAME = fract_ol
SRCS = fracto_utils.c
OBJS = $(SRCS:.c=.o)

MLX_PATH = ./minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
CC	 = cc
RM	 = rm -f
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a



.PHONY: all clean fclean re

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_PATH)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX_PATH) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all