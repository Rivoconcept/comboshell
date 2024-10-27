# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:39:35 by rhanitra          #+#    #+#              #
#    Updated: 2024/10/27 19:24:06 by rhanitra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS = check_behavior.c ft_isbuiltins.c ft_strcmp.c ft_var_in_apostrophe.c \
		check_cmd_builtins.c ft_isspace.c ft_cmpstr.c \
		ft_check_quotes.c ft_is_token.c ft_strcpy.c \
		find_first_index.c ft_len.c ft_strdup.c \
		find_token_type.c ft_match_char.c ft_strncpy.c \
		format_input.c ft_memcpy.c ft_strndup.c \
		format_quotes.c ft_memset.c ft_strsize.c \
		format_str_without_quote.c ft_parser.c ft_putchar_count.c ft_subfirst.c \
		free.c generate_prompt.c \
		ft_bzero.c ft_putchar_fd.c handle_quotes.c \
		ft_check_input.c ft_putstr_fd.c handle_signal.c \
		ft_check_str.c ft_realloc.c ft_joinstr.c \
		ft_free_array.c ft_strcat.c ft_del_quote.c

CFLAGS = -Wextra -Wall -Werror -Wall -Wextra -Werror

CC = cc

SRC = $(UTILS)

OBJ = $(SRC:.c=.o)

RM = rm -rf

AR = ar rcs

NAME = libutils.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

clean :
	$(RM) $(OBJ)
	
fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
