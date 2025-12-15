NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = parsing/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = main.c src/utils/util.c src/assets/imgs.c src/assets/moves.c src/assets/ray_caster.c \
      src/window.c src/utils/lib_ft.c src/assets/wall_projection.c \
      parsing/pars_src/utils/texture_loader.c parsing/pars_src/utils/texture_render.c \
      parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c \
      parsing/pars_src/utils/map_utils.c parsing/pars_src/utils/map_utils1.c \
      parsing/pars_src/utils/parce_utils.c parsing/pars_src/utils/utils.c \
      parsing/pars_src/utils/utils1.c parsing/pars_src/utils/texture_validation.c \
      parsing/pars_src/parse.c parsing/pars_src/tools.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) MLX422/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I./MLX422/include -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
