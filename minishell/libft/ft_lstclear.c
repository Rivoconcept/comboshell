/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:37:51 by rhanitra          #+#    #+#             */
/*   Updated: 2024/03/11 09:38:50 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*before;

	if (lst && *lst && del)
	{
		before = (t_list *)*lst;
		while (before)
		{
			temp = before->next;
			ft_lstdelone(before, del);
			before = temp;
		}
		*lst = NULL;
	}
}
