/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:53:27 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/15 08:36:59 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int			i;
	unsigned char			*str;
	unsigned char			to_find;

	str = (unsigned char *)s;
	to_find = (unsigned char)c;
	i = 0;
	while (n--)
	{
		if (str[i] == to_find)
			return ((void *)(unsigned char *)&str[i]);
		i++;
	}
	return (0);
}
