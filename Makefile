SRC= test.c #src/main.c \

OBJS= $(SRC:.c=.o)

NAME= cub3d

CC= cc

CFLAGS= -Wall -Wextra -Werror

all:$(NAME)

$(NAME):$(OBJS) inc/cub3d.h
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz -Imlx_linux  -o $(NAME)

%.o:%.c inc/cub3d.h
	$(CC)  -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re:fclean all

.PHONY: clean
