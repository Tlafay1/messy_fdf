CC = gcc

NAME = fdf

CFLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -L ../minilibx_macos -L ../srcs/libft -lmlx -lm -lft -framework OpenGL -framework AppKit

INC_FLAGS = -I ../minilibx_macos -I /opt/X11/include

SRCS = rolled.c images.c calc.c

OBJS = ${SRCS:.c=.o} 

#INCLUDES = main.h coordinates.h

RM  = rm -f 

all : $(NAME)

$(NAME) : $(OBJS) $(INCLUDES)
	$(MAKE) -C ../srcs/libft
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(INC_FLAGS) -c $< 

clean :
	$(MAKE) -C ../srcs/libft $@
	$(RM) $(OBJS)

fclean : clean
	$(MAKE) -C ../srcs/libft $@
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
.SILENT :