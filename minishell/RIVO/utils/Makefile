#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:39:35 by rhanitra          #+#    #+#              #
#    Updated: 2024/10/18 11:13:23 by rhanitra         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

UTILS = ft_free_array.c ft_isspace.c ft_strcmp.c ft_strncpy.c ft_match_char.c \
		check_quotes.c find_first_index.c putchar_count.c \
		ft_strsize.c token_type.c format_quotes.c handle_quotes.c \
		ft_putchar_fd.c ft_putstr_fd.c generate_prompt.c handle_signal.c
		

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
	$(RM) *.o
	
fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
