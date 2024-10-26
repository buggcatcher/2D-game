NAME = so_long
CC = cc
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror -g
LINKS_LINUX = -lX11 -lm -lXext -lz
MINILIBX = mlx/libmlx.a
INCLUDES = -Imlx -Ilibft
LIBS = -Lmlx -lmlx -Llibft -lft
SRC = main.c parse.c parse2.c parse3.c utils.c utils2.c \
	  map_gen.c game.c render.c \
		
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/ 
	make -C mlx/       
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBS) $(LINKS_LINUX) -o $(NAME) 

$(LIBFT):
	make -C libft    

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@  

clean:
	rm -f $(OBJ)        
	make -C libft clean
	make -C mlx clean   

fclean: clean
	rm -f $(NAME)       
	make -C libft fclean
	make -C mlx clean   

re: fclean all

.PHONY: all clean fclean re libft
