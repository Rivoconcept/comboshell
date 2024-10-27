/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:09:54 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 18:15:04 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
	if (start > ft_strsize(s))
		size = 1;
	else
		size = trunc_size(s, start, len) + 1;
	new = (char *)malloc(size * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < size)
		((unsigned char *)new)[i++] = '\0';
	if (ft_strsize(s) >= start)
		ft_strncat(new, s + start, len);
	return (new);
}

char	*ft_substrj(char *s, unsigned int start, size_t len)
{
	char	*new;
	int		size;
	int		i;

	i = 0;
	if (start > ft_strsize(s))
		size = 1;
	else
		size = trunc_size(s, start, len) + 1;
	new = (char *)malloc(size * sizeof(char));
	if (new == NULL)
		return (NULL);
	while (i < size)
		((unsigned char *)new)[i++] = '\0';
	if (ft_strsize(s) >= start)
		ft_strncat(new, s + start, len);
	free(s);
	return (new);
}