/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:00:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/24 15:46:50 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
//#include <bsd/string.h>
#include <string.h>
#include "libft.h"

int	check_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	char	*str;
	size_t	stop;
	size_t	start;

	if (!s1 || !set)
		return (0);
	i = 0;
	start = 0;
	while (*(s1 + start) && check_set(s1[start], set))
		start++;
	stop = ft_strlen(s1);
	while (stop > start && check_set(s1[stop - 1], set))
		stop--;
	str = (char *)malloc(sizeof(char) * ((stop - start + 1)));
	if (!str)
		return (0);
	while ((start + i) < stop)
	{
		str[i] = s1[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
