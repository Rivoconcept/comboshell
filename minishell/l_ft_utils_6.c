/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_utils_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:09:54 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/08 14:22:07 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strncat(char *destination, const char *source, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (destination[len] != '\0')
	{
		len++;
	}
	while (source[i] != '\0' && i < size)
	{
		destination[len] = source[i];
		i++;
		len++;
	}
	destination[len] = '\0';
	return (destination);
}

static int	trunc_size(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s[start++] != '\0')
		i++;
	return (i);
}

char	*ft_subfirst(char *s, unsigned int start, size_t len)
{
	char	*new;
	int		size;
	int		i;

	i = 0;
	if (start > ft_strlen(s))
		size = 1;
	else
		size = trunc_size(s, start, len) + 1;
	new = (char *)malloc(size * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < size)
		((unsigned char *)new)[i++] = '\0';
	if (ft_strlen(s) >= start)
		ft_strncat(new, s + start, len);
	return (new);
}

char	*ft_substrj(char *s, unsigned int start, size_t len)
{
	char	*new;
	int		size;
	int		i;

	i = 0;
	if (start > ft_strlen(s))
		size = 1;
	else
		size = trunc_size(s, start, len) + 1;
	new = (char *)malloc(size * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < size)
		((unsigned char *)new)[i++] = '\0';
	if (ft_strlen(s) >= start)
		ft_strncat(new, s + start, len);
	free(s);
	return (new);
}

char *join_argv(char **argv)
{
    int i;
    char *new_str;
    char *temp = NULL;

    i = 1;
    new_str = ft_strdup(argv[0]);
    if (!new_str)
        return (NULL);
    while (argv[i] != NULL)
    {
        temp = ft_strjoin(new_str, " ");
        free(new_str);
        new_str = temp;
        temp = ft_strjoin(new_str, argv[i]);
        free(new_str);
        new_str = temp;
        i++;
    }
    return (new_str);
}