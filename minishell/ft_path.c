/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:33:46 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 12:33:46 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char *envp[], char *rgx)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 0;
	j = 0;
	value = NULL;
	while (envp[i] != NULL)
	{
		while (envp[i][j] != '=')
			j++;
		key = ft_subfirst(envp[i], 0, j);
		if (ft_strcmp(key, rgx) == 0)
		{
			value = ft_subfirst(envp[i], (j + 1), ft_strlen(envp[i]));
			break ;
		}
		free(key);
		j = 0;
		i++;
	}
	free(key);
	return (value);
}
