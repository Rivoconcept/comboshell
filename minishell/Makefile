# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/11 13:00:11 by rhanitra          #+#    #+#              #
#    Updated: 2024/12/22 20:54:43 by rrakoton         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = r_check_behavior.c r_check_quotes.c r_format_argv.c r_ft_cd_1.c \
			r_format_cmd.c r_format_input.c r_format_quotes.c r_ft_cd_2.c \
			r_ft_cleaner.c r_ft_echo.c r_ft_export_1.c r_ft_export_2.c \
			r_ft_export_3.c r_ft_export_4.c r_ft_exit.c  r_ft_utils_5.c\
			r_ft_is_token.c r_ft_pwd.c r_ft_utils_1.c r_ft_utils_2.c r_exec.c \
			r_ft_utils_3.c r_ft_utils_4.c r_handle_quotes.c r_init_list_cmd.c \
			r_ft_env_1.c r_ft_env_2.c r_ft_env_3.c r_init_list_params.c \
			r_ft_parser.c r_signal.c r_ft_builtins.c main.c r_utils.c  r_ft_unset.c \
			l_here_doc.c l_here_doc_utils.c l_ft_utils_6.c l_ft_utils_5.c \
			l_ft_check.c l_redirection.c l_inout_utils.c l_del_utils.c l_expand.c \
			l_handle_here.c


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
	$(RM) $(EXEC)
	$(MAKE) -C $(DIR_LIBFT) fclean

re : fclean all

.PHONY: all clean fclean re