/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:31:53 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:49:22 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **cmd, t_params *params)
{
	int	i;

	i = 1;
	while (cmd[i] != NULL)
	{
		del_env_element(&params->myenvp, cmd[i]);
		i++;
	}
	return (0);
}
