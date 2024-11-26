SRC = main.c get_next_line.c get_next_line_utils.c ft_atoi.c ft_split.c

INCLUDES = ./includes
CC = cc

FLAGS = -Wall -Werror -Wextra -lX11 -lXext -lmlx -g -lm

NAME = fdf

all : ${NAME}

${NAME} :
	${CC} ${SRC} ${FLAGS} -o ${NAME}

re : clean all

clean :
	rm fdf

fclean :
	rm -rf fdf
