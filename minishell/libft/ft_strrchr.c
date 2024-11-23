/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:58:59 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/22 08:42:23 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char const	*pos;

	pos = NULL;
	while (*s)
	{
		if (*s == (char)c)
			pos = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return ((char *)pos);
}
