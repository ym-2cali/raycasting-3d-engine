LIBFT_DIR = parsing/libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC= src/main.c src/assets/imgs.c src/assets/moves.c src/assets/ray_caster.c src/window.c src/utils/lib_ft.c parsing/pars_src/utils/texture_loader.c src/assets/wall_projection.c \
	parsing/get_next_line/get_next_line.c parsing/get_next_line/get_next_line_utils.c parsing/pars_src/utils/map_utils.c parsing/pars_src/utils/map_utils1.c parsing/pars_src/utils/map_utils2.c parsing/pars_src/utils/map_utils3.c parsing/pars_src/utils/parce_utils.c parsing/pars_src/utils/parce_utils2.c \
    parsing/pars_src/utils/utils.c parsing/pars_src/utils/utils1.c parsing/pars_src/utils/utils2.c parsing/pars_src/utils/parse.c parsing/pars_src/utils/texture_validation.c parsing/pars_src/utils/garbage_collector.c src/assets/ray_caster_utils.c 

OBJS= $(SRC:.c=.o)

NAME= cub3d

CC= cc

CFLAGS= -Wall -Wextra -Werror

all:$(NAME)

$(NAME):$(OBJS) $(LIBFT) inc/cub3d.h
	$(CC) $(CFLAGS) $(OBJS)  $(LIBFT) MLX422/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)
#linux  MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm 	
#wsl -I./MLX42/include -L./MLX42/build -lmlx42 -ldl -lglfw -pthread -lm

%.o:%.c inc/cub3d.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean:clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re:fclean all

.PHONY: clean
