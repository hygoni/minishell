NAME = minishell
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=4096
SRCS = ${addprefix srcs/, ${shell ls srcs | grep '\.c'}} ${addprefix builtin/, ${shell ls builtin | grep '\.c'}}
OBJS = ${SRCS:.c=.o}
CC = gcc
RM = rm -f
INC = -I./includes
LIBFT = -L./libft -lft

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${INC} ${LIBFT} ${OBJS} -o ${NAME}

%.o : %.c
	${CC} ${CFLAGS} ${INC} -c $< -o $@ -g

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
