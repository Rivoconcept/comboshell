/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:35:09 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 11:35:09 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int count_array (char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
        i++;
    return i;
}

void	*ft_free(char **ar, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
	return (NULL);
}