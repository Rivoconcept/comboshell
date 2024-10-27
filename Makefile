NAME = minishell

LIBFT = libft.a

FLAGS_READLINE = -lreadline

SRC = exec.c ft_cmd.c ft_multiline.c ft_path.c here_doc_utils.c here_doc.c \
	list.c guards.c main.c node.c parser.c quote.c real_path.c scanner.c \
	signal.c tokens.c vector.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Wextra -Werror

CC = cc

all : $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(FLAG) $(LIBFT) -o $(NAME) $(FLAGS_READLINE)

$(LIBFT) : $(OBJ)
	make -C ./LIBFT/
	cp ./LIBFT/libft.a ./
	ar rcs $(LIBFT) $(OBJ)
	
.c.o:
	${CC} ${FLAGS} -o ${<:.c=.o} -c $<
	
clean:
	make clean -C ./LIBFT/
	rm -f $(OBJ)

fclean: clean
	make fclean -C ./LIBFT/
	rm -f $(LIBFT)

re: fclean all
