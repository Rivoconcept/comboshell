/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_in_apostrophe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:24:16 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 18:24:57 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	var_in_apostrophe(char *input, int i)
{
	int	nbr;
	int	j;

	nbr = 0;
	if (input[i] == '$')
	{
		j = 0;
		nbr = 0;
		while (j < i)
		{
			if (input[j] == '\'')
				nbr++;
			j++;
		}
		if (nbr % 2 != 0)
			return (1);
	}
	return (0);
}
