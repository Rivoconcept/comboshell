/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:41:59 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 18:16:31 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;
	size_t		i;
	size_t		len;

	if (size > ft_strsize((char *)s))
		len = ft_strsize((char *)s);
	else
		len = size;
	str = malloc(len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = ((char *)s)[i];
		i++;
	}
	str[i] = 0;
	return (str);
}