/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:25:23 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 17:25:45 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_input(char *s, char *base)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		found = 0;
		while (base[j] != '\0')
		{
			if (s[i] == base[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (!found)
			return (0);
		i++;
	}
	return (1);
}
