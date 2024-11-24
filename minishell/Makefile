# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:39:35 by rhanitra          #+#    #+#              #
#    Updated: 2024/11/24 14:45:44 by rhanitra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = l_child_process.c l_exec_utils.c l_exec.c l_free.c l_ft_check.c \
			l_ft_multiline.c l_ft_strcmp.c l_ft_utils_5.c l_ft_utils_6.c \
			l_guards.c l_here_doc_utils.c l_here_doc.c l_list.c l_node.c \
			l_parser.c l_quote.c l_real_path.c l_redirection_utils.c \
			l_redirection.c l_scanner.c l_signal.c l_tokens.c \
			l_vector.c main.c \
			#r_check_behavior.c r_check_quotes.c r_format_argv.c \
			r_format_cmd.c r_format_input.c r_format_quotes.c r_ft_cd1.c \
			r_ft_cd2.c r_ft_cleaner.c r_ft_echo.c r_ft_env.c r_ft_export.c \
			r_ft_is_token.c r_ft_pwd.c r_ft_utils_1.c r_ft_utils_2.c \
			r_ft_utils_3.c r_ft_utils_4.c r_handle_quotes.c \
			r_init_list_env.c r_init_list_params.c r_main.c \
			r_parser.c r_signal.c

DIR_MINISHELL = ./
SRC_MINISHELL = $(addprefix $(DIR_MINISHELL),$(MINISHELL))

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

OBJ_MINISHELL = $(SRC_MINISHELL:.c=.o)

EXEC = minishell

CFLAGS = -Wall -Wextra -Werror -g -I $(DIR_LIBFT)
CC = cc
RM = rm -rf
AR = ar rcs

all : $(EXEC)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	$(MAKE) -C $(DIR_LIBFT)

$(EXEC) : $(OBJ_MINISHELL) $(LIBFT)
	$(CC)  $(CFLAGS) -o $@ $^ -L$(DIR_LIBFT) -lft -lreadline

clean :
	$(RM) $(OBJ_MINISHELL)
	$(MAKE) -C $(DIR_LIBFT) clean

fclean : clean
	$(RM) $(EXEC)
	$(MAKE) -C $(DIR_LIBFT) fclean

re : fclean all

.PHONY: all clean fclean re

