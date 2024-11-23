/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:22:02 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 18:52:30 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_del_quotes(char **argv)
{
	int		i;
	char	*temp;

	i = 0;
	while (argv[i] != NULL)
	{
		temp = format_quotes(argv[i]);
		free(argv[i]);
		argv[i] = temp;
		i++;
	}
}
