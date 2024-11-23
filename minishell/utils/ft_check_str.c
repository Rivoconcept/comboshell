/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:24:24 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 18:15:56 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_str(const char *big, const char *little, char *check)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strsize((char *)little);
	if (!*little || !check_input((char *)big, check))
		return (0);
	while (big[i] != '\0' && len > 0)
	{
		j = 0;
		if (big[i] == little[j] && i != 0)
		{
			while (little[j] && j < len && big[i + j] == little[j])
				j++;
			if (little[j] == '\0')
				return (i);
		}
		i++;
	}
	return (0);
}
