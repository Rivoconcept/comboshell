/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:21:59 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 17:56:11 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	isbuiltins(char *command)
{
	int		i;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};

	i = 0;
	while (builtins[i] != NULL)
	{
		if (!ft_strcmp(command, builtins[i])
			&& ft_strsize(command) == ft_strsize(builtins[i]))
			return (1);
		i++;
	}
	return (0);
}
