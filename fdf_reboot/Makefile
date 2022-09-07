CC = gcc

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -L ../minilibx_macos -L ../srcs/libft -lmlx -lm -lft -framework OpenGL -framework AppKit

INC_FLAGS = -I ../minilibx_macos

SRCS = main.c draw.c events.c utils.c rotations.c parsing.c

OBJS = ${SRCS:.c=.o} 

INCLUDES = main.h

RM  = rm -f 

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDES)
	$(MAKE) -C ../srcs/libft
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(INC_FLAGS) $(CFLAGS) -c $<

clean :
	$(MAKE) -C ../srcs/libft $@
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C ../srcs/libft $@
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
.SILENT :