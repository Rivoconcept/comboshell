/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:55:48 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/20 12:53:14 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../libft/libft.h"
# include "../utils/utils.h"
# include "../minishell.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

#include <ctype.h>


int					is_operator(char *str);
t_params			*create_params(char **argv);
void				append_params(t_params **params_list, char **argv);
void				free_list_params(t_params *params);
int					ft_argvlen(char **argv, int *index);
t_params			*parse_command_into_params(char **argv, char const *input);

void				print_argv(char **argv);
int					check_input(char *s, char *base);
int					check_str(const char *big, const char *little, char *check);
int					check_behavior(char *s);

char				*format_input(char *input, char *operators);

char				**put_argv(char **argv, char *input);
void				free_array(char **arr);
void				free_list_params(t_params *params);
int					execution(char **argv, char **envp);
char				**parse_command(const char *str);
char    			*format_str_without_quote(char *input);
int					while_check_char(char c, char *input);



#endif
