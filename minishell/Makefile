# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:39:35 by rhanitra          #+#    #+#              #
#    Updated: 2024/10/27 18:37:25 by rhanitra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = child_process.c clean_arg.c exec_utils.c exec.c ft_check.c ft_cmd.c ft_multiline.c ft_path.c \
	here_doc_utils.c here_doc.c list.c guards.c main.c node.c parser.c quote.c real_path.c \
	redirection.c redirection_utils.c scanner.c signal.c tokens.c vector.c format_argv.c format_cmd.c

DIR_MINISHELL = ./
SRC_MINISHELL = $(addprefix $(DIR_MINISHELL),$(MINISHELL))

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_UTILS = ./utils
UTILS = $(DIR_UTILS)/libutils.a

DIR_BUILTINS = ./builtins

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
	$(CC)  $(CFLAGS) -o $@ $^ -L$(DIR_LIBFT) -lft -L$(DIR_UTILS) -lutils -lreadline

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

