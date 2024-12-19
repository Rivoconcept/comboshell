/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 09:50:18 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/23 08:39:42 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <unistd.h>
#include <sys/types.h>
// #include <stdio.h>
// #include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int		i;
	unsigned char		*p;

	p = s;
	i = 0;
	while (n != 0)
	{
		p[i] = 0;
		i++;
		n--;
	}
}
