/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:20:21 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 19:23:25 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// check_behavior.c
int			check_error_newline(char *s);
int			check_behavior(char *s);

// check_cmd_builtins.c
char		*check_cmd_builtins(char *command);

// find_first_index.c
int			find_first_index(const char *big, const char *little);

// find_token_type.c
int			check_variable(char *arg);
int			token_type(char *arg);

// format_input.c
char		*format_input(char *input, char *operators);

// format_quotes.c
char		*format_quotes(char *command);

// format_str_without_quote.c
char		*format_str_without_quote(char *input);

// free.c
int			count_array(char **argv);
void		*ft_free(char **ar, int index);

// ft_bzero
void		ft_bzero(void *str, size_t n);

// ft_check_input.c
int			check_input(char *s, char *base);

// ft_check_quotes.c
int			in_apostrophe(char *str);
int			in_quote(char *str);
int			pure_apostrophe(char *str);
int			pure_quote(char *str);
int			in_single_quote(char *str);
int			in_double_quote(char *str);

// ft_check_str.c
int			check_str(const char *big, const char *little, char *check);

// ft_cmpstr.c
int			ft_cmpstr(const char *s1, const char *s2);

// ft_del_quote.c
void		ft_del_quotes(char **argv);

// ft_free_array.c
void		free_array(char **arr);

// ft_is_token.c
int			token_type(char *arg);

// ft_isbuiltins.c
int			isbuiltins(char *command);

// ft_isspace.c
int			ft_isspace(char c);

// ft_joinstr.c
char		*ft_joinstr(char const *s1, char const *s2);

// ft_len.c
size_t		ft_sublen(char **s);

// ft_match_char.c
int			while_check_char(char c, char *input);

// ft_memcpy.c
void		*ft_memcpy(void *dest, const void *src, size_t len);

// ft_memset.c
void		*ft_memset(void *str, int c, size_t n);

// ft_parser.c
char		**parse_command(char const *input);

//ft_putchar_count.c
int putchar_count(const char *src, char c);

// ft_putchar_fd.c
int			ft_putcharfd(char c, int fd);

// ft_putstr_fd.c
int			ft_putstrfd(char *s, int fd);

// ft_realloc.c
void		*ft_realloc(void *ptr, size_t new_size);

// ft_strcat.c
char		*ft_strcat(char *dest, char *src);

// ft_strcmp.c
int			ft_strcmp(const char *first, const char *second);

// ft_strcpy.c
char		*ft_strcpy(char *s1, char *s2);

// ft_strdup.c
char		*ft_strdup(const char *s);

// ft_strncpy.c
char		*ft_strncpy(char *dest, const char *src, size_t n);

// ft_strndup.c
char		*ft_strndup(const char *s, size_t size);

// ft_strsize.c
size_t		ft_strsize(char *str);

// ft_subfirst.c
char		*ft_subfirst(char *s, unsigned int start, size_t len);
char		*ft_substrj(char *s, unsigned int start, size_t len);

// ft_var_in_apostrophe.c
int			var_in_apostrophe(char *input, int i);

// generate_prompt.c
void		print_prompt(void);

// handle_quotes.c
void		handle_quotes(char c, int *in_single_quote, int *in_double_quote);

// handle_signal.c
void		handle_sigint(int sig);
void		handle_sigquit(char *input);
void		handle_sigignor(int sig);

#endif
