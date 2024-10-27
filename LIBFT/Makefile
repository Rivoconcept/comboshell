SRCS	=	free.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_len.c ft_memcpy.c ft_memset.c \
			ft_putchar_fd.c ft_split.c ft_putendl_fd.c ft_putstr_fd.c ft_realloc.c ft_strcat.c \
			ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c \
			ft_strjoin.c ft_strndup.c ft_subfirst.c

OBJ 	=	$(SRCS:.c=.o)

NAME	=	libft.a
FLAGS	=	-Wall -Wextra -Werror
cc		=	cc

.c.o:
	${CC} ${FLAGS} -c $< -o $@


all: ${NAME}

${NAME}: ${OBJ}
	@ar rc ${NAME} ${OBJ}

clean:
	rm -rf ${OBJ}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all, clean, fclean, re