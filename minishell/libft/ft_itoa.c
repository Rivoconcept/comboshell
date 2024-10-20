/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 08:13:27 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/11 08:17:41 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	n_len(int n)
{
	long	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int			i;
	int long	nbr;
	int			size;
	char		*str;

	i = 0;
	nbr = (int long)n;
	size = n_len(nbr);
	str = (char *)malloc(sizeof(char) * size + 1);
	if (!str)
		return (0);
	str[size] = '\0';
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
		i++;
	}
	while (i < size)
	{
		str[--size] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (str);
}
