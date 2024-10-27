/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:20:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 15:49:26 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

int		ft_isspace(char c);
char	**parse_command(const char *str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		while_check_char(char c, char *input);
void print_prompt(); 
int pure_apostrophe(char *str);
int pure_quote(char *str);
int in_single_quote(char *str);
int     in_double_quote(char *str);

int		putchar_count(const char *src, char c);
int		find_first_index(const char *big, const char *little);
int		ft_strsize(char *str);
int     token_type(char *arg);
char    *format_quotes(char *command);
int echap_quote(char c, int *in_single_quote, int *in_double_quote);
void    handle_quotes(char c, int *in_single_quote, int *in_double_quote);
int	ft_putcharfd(char c, int fd);
int	ft_putstrfd(char *s, int fd);
void handle_sigint(int sig);
void handle_sigignor(int sig);
void handle_sigquit(char *input);

#endif
