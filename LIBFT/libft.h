/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:50:42 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 12:50:42 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// free.c
int count_array (char **argv);
void	*ft_free(char **ar, int index);

// ft_bzero.c
void	ft_bzero(void *str, size_t n);

// ft_calloc.c
void	*ft_calloc(size_t nmemb, size_t size);

// ft_isalnum.c
int	ft_isalnum(int c);

// ft_memcpy.c
void *ft_memcpy(void *dest, const void *src, size_t len);

// ft_len.c
size_t	ft_strlen(const char *s);
size_t	ft_sublen(char **s);

// ft_memset.c
void	*ft_memset(void *str, int c, size_t n);

// ft_putchar_fd.c
void	ft_putchar_fd(char c, int fd);

// ft_putendl_fd.c
void	ft_putendl_fd(char *s, int fd);

// ft_putstr_fd.c
void	ft_putstr_fd(char *s, int fd);

// ft_realloc.c
void		*ft_realloc(void *ptr, size_t size);

// ft_split.c
char	**ft_split(char *s, char c);

// ft_strcat.c
char *ft_strcat(char *dest, char *src);

// ft_strchr.c
char	*ft_strchr(const char *string, int searchedChar);

// ft_strcmp.c
int	ft_strcmp(const char *first, const char *second);

// ft_strcpy.c
char    *ft_strcpy(char *s1, char *s2);

// ft_strdup.c
char	*ft_strdup(const char *s);

// ft_strjoin.c
char	*ft_strjoin(char *s1, char const *s2);

// ft_strndup.c
char	*ft_strndup(const char *s, size_t size);

// ft_subfirst.c
char	*ft_subfirst(char *s, unsigned int start, size_t len);
char	*ft_substr(char *s, unsigned int start, size_t len);


#endif
