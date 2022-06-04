NAME	= fdf
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra
INC		= -I includes -I libft/includes -I minilibx
LIBFT	= -I libft/includes -L libft -lft
LIBMLX	= -I minilibx  -L minilibx -lmlx_Linux
LIBSTD	= -lX11 -lXext -lmlx -Lmlx -lm -ldl
SRC		= srcs/error.c	srcs/fdf.c	srcs/graphic_process.c \
			srcs/graphic_hook.c	srcs/parse_fdf.c  srcs/graphic_render.c \
			srcs/set_color.c
OBJ		= $(SRC:.c=.o)
RM		= rm -f

all		: $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	make -C minilibx
	$(CC) -o $@ $^ $(LIBFT) $(LIBMLX) $(LIBSTD)

.c.o	:
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY	: all clean fclean re

clean	:
	make clean -C libft
	make clean -C minilibx
	$(RM) $(OBJ)

fclean	: clean
	$(RM) libft/libft.a
	$(RM) minilibx/libmlx_Linux.a
	$(RM) $(NAME)

re		: fclean
	make all
