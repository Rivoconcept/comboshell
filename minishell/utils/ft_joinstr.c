/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 08:55:06 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 18:19:23 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_joinstr(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strsize((char *)s1) 
		+ ft_strsize((char *)s2)) + 1);
	if (!str)
		return (0);
	if (s1)
	{
		while (s1[i] != '\0')
			str[i++] = s1[j++];
	}
	j = 0;
	if (s2)
	{
		while (s2[j] != '\0')
			str[i++] = s2[j++];
	}
	return (str[i] = '\0', str);
}
