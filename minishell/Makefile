# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:00:11 by rhanitra          #+#    #+#              #
#    Updated: 2024/12/23 13:55:49 by rhanitra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = r_check_behavior.c r_format_argv_1.c r_format_argv_2.c \
			r_ft_cd_1.c r_ft_unset.c r_ft_history.c \
			r_format_cmd_1.c r_format_cmd_2.c r_format_input.c r_ft_cd_2.c \
			r_format_quotes_1.c r_format_quotes_2.c r_format_quotes_3.c \
			r_ft_cleaner.c r_ft_echo.c r_ft_export_1.c r_ft_export_2.c \
			r_ft_export_3.c r_ft_export_4.c r_ft_exit.c  r_ft_utils_5.c \
			r_ft_pwd.c r_ft_utils_1.c r_ft_utils_2.c r_exec.c \
			r_ft_utils_3.c r_ft_utils_4.c r_ft_utils_5.c \
			get_next_line.c get_next_line_utils.c \
			r_ft_env_1.c r_ft_env_2.c r_ft_env_3.c  \
			r_ft_parser.c r_signal.c r_ft_builtins.c main.c   \
			l_here_doc.c l_here_doc_utils.c l_ft_utils_6.c l_ft_utils_7.c  \
			l_ft_check.c l_redirection.c l_inout_utils.c l_del_utils.c \
			l_expand.c l_handle_here.c \
			   
DIR_MINISHELL = ./
SRC_MINISHELL = $(addprefix $(DIR_MINISHELL),$(MINISHELL))

DIR_LIBFT = ./libft
LIBFT = $(DIR_LIBFT)/libft.a

OBJ_MINISHELL = $(SRC_MINISHELL:.c=.o)

EXEC = minishell

CFLAGS = -Wall -Wextra -Werror -g -I $(DIR_LIBFT)
CC = gcc
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
	$(RM) $(EXEC) .old_history .readline.ign
	$(MAKE) -C $(DIR_LIBFT) fclean

re : fclean all

.PHONY: all clean fclean re