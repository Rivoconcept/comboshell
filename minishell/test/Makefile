#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:39:35 by rhanitra          #+#    #+#              #
#    Updated: 2024/10/16 14:14:13 by rhanitra         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

MINISHELL = test.c

DIR_MINISHELL = ./
SRC_MINISHELL = $(addprefix $(DIR_MINISHELL),$(MINISHELL))

DIR_LIBFT = ../libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_UTILS = ../utils
UTILS = $(DIR_UTILS)/libutils.a

DIR_BUILTINS = ../builtins

OBJ_MINISHELL = $(SRC_MINISHELL:.c=.o)

EXEC = minishell

CFLAGS = -Wall -Wextra -Werror -g -I $(DIR_LIBFT) -I $(DIR_UTILS) -I $(DIR_BUILTINS)
CC = cc
RM = rm -rf
AR = ar rcs

all : $(EXEC)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)

$(UTILS):
	$(MAKE) -C $(DIR_UTILS)
	$(MAKE) -C $(DIR_BUILTINS)


$(EXEC) : $(OBJ_MINISHELL) $(LIBFT) $(UTILS)
	$(CC)  $(CFLAGS) -o $@ $^ -L$(DIR_LIBFT) -lft -L$(DIR_UTILS) -lutils

clean :
	$(RM) $(OBJ_MINISHELL)
	$(MAKE) -C $(DIR_LIBFT) clean
	$(MAKE) -C $(DIR_UTILS) clean
	$(MAKE) -C $(DIR_BUILTINS) clean

fclean : clean
	$(RM) $(EXEC)
	$(MAKE) -C $(DIR_LIBFT) fclean
	$(MAKE) -C $(DIR_UTILS) fclean
	$(MAKE) -C $(DIR_BUILTINS) fclean

re : fclean all

.PHONY: all clean fclean re

