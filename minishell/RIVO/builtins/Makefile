# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 08:39:35 by rhanitra          #+#    #+#              #
#    Updated: 2024/10/27 15:41:55 by rhanitra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_ECHO = echo.c
FT_CD = cd.c
FT_PWD = pwd.c

DIR_FT_ECHO = ./
SRC_FT_ECHO = $(addprefix $(DIR_FT_ECHO),$(FT_ECHO))

DIR_FT_CD = ./
SRC_FT_CD = $(addprefix $(DIR_FT_CD),$(FT_CD))

DIR_FT_PWD = ./
SRC_FT_PWD = $(addprefix $(DIR_FT_PWD),$(FT_PWD))

DIR_LIBFT = ../../libft
LIBFT = $(DIR_LIBFT)/libft.a

DIR_UTILS = ../utils
UTILS = $(DIR_UTILS)/libutils.a

OBJ_FT_ECHO = $(SRC_FT_ECHO:.c=.o)
OBJ_FT_CD = $(SRC_FT_CD:.c=.o)
OBJ_FT_PWD = $(SRC_FT_PWD:.c=.o)

ECHO = ./exec/echo
CD = ./exec/cd
PWD = ./exec/pwd

CFLAGS = -Wall -Wextra -Werror -g -I $(DIR_LIBFT) -I $(DIR_UTILS)
CC = cc
RM = rm -rf

all : $(ECHO) $(CD) $(PWD)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(ECHO) : $(OBJ_FT_ECHO) $(LIBFT)  $(UTILS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR_LIBFT) -lft -L$(DIR_UTILS) -lutils

$(CD) : $(OBJ_FT_CD) $(LIBFT)  $(UTILS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR_LIBFT) -lft -L$(DIR_UTILS) -lutils

$(PWD) : $(OBJ_FT_PWD) $(LIBFT)  $(UTILS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(DIR_LIBFT) -lft -L$(DIR_UTILS) -lutils

clean :
	$(RM) $(OBJ_FT_ECHO)
	$(RM) $(OBJ_FT_CD)
	$(RM) $(OBJ_FT_PWD)
	
fclean : clean
	$(RM) $(ECHO)
	$(RM) $(CD)
	$(RM) $(PWD)

re : fclean all

.PHONY: all clean fclean re
