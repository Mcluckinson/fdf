NAME = fdf

SOURCE = fdf.c attune_lines.c buttons.c draw_line.c draw_map.c get_lines.c read_map.c window_works.c arrows.c\
altitude.c gradient.c ft_atoi_base.c

OBJ = $(patsubst %.c,%.o,$(SOURCE))


LIB = -L libft -lft
OGK = -framework OpenGL
APK = -framework AppKit
LMX = -lmlx

all: $(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -g -c -o $@ $<

$(NAME): $(OBJ)
	make -C ./libft
	gcc -o $(NAME) $(SOURCE:.c=.o) $(LIB) $(OGK) $(APK) $(LMX)

clean:
	/bin/rm -f $(SOURCE:.c=.o)
	make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
