SRC= src/main.c src/assets/imgs.c src/assets/moves.c src/utils/libft.c #test.c \

OBJS= $(SRC:.c=.o)

NAME= cub3d

CC= cc

CFLAGS= -Wall -Wextra -Werror

all:$(NAME)

$(NAME):$(OBJS) inc/cub3d.h
	$(CC) $(OBJS) MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

%.o:%.c inc/cub3d.h
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY: clean
