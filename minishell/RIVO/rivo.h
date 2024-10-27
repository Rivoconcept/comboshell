/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rivo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 13:55:48 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 15:45:47 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RIVO_H
# define RIVO_H

# include "../libft/libft.h"
# include "./utils/utils.h"
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


typedef struct s_params
{
	char			**str;
	int				status;
	struct s_params	*next;
}					t_params;

int					is_operator(char *str);
t_params			*create_params(char **argv);
void				append_params(t_params **params_list, char **argv);
void				free_list_params(t_params *params);
int					ft_argvlen(char **argv, int *index);
t_params			*parse_command_into_params(char **argv, char const *input);

int					check_input(char *s, char *base);
int					check_str(const char *big, const char *little, char *check);
int					check_behavior(char *s);

char				*format_input(char *input, char *operators);
int					isbuiltins(char *command);
char				*check_cmd_builtins(char *command);
char				**put_argv(char **argv, char *input, t_params *params);
void				free_array(char **arr);
void				free_list_params(t_params *params);
int 				execution(char **argv, char **envp, t_params *params);
char				**parse_command(const char *str);
char				*format_str_without_quote(char *input);
int					while_check_char(char c, char *input);
char				*format_quotes(char *command);
void 				format_variable(char **argv, t_params *params);
void				del_quotes(char **argv);

#endif
