/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:44:19 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/11 09:46:43 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	if (lst != NULL)
	{
		while (lst != NULL)
		{
			++size;
			lst = lst->next;
		}
	}
	return (size);
}
