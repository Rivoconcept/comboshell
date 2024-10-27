/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:20:27 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 18:02:46 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*check_cmd_builtins(char *command)
{
	int		i;
	char	*full_path;
	char	*path;
	char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};

	i = 0;
	path = "./builtins/exec/";
	full_path = NULL;
	while (builtins[i] != NULL)
	{
		if (!ft_strcmp(command, builtins[i]))
		{
			full_path = ft_joinstr(path, builtins[i]);
			if (full_path == NULL)
				return (NULL);
			break ;
		}
		i++;
	}
	return (full_path);
}
