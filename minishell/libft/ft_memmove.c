/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:54:41 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/15 08:49:12 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>

void	*ft_memmove(void *target, void const *source, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)source;
	d = (char *)target;
	i = 0;
	if (!target && !source)
		return (target);
	if (target == source)
		return (target);
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (n--)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (target);
}
