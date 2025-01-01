/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/01 18:40:24 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_pipe(char **cmd, t_params *params)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		// || (isoperators(cmd[i]) && ft_strncmp(cmd[i], "|",
		// 			ft_strlen(cmd[i])))
		if (check_return_zero(cmd[i], params))
			return (1);
		else if (((isoperators(cmd[i]) && cmd[i + 1] == NULL)
				&& ft_strncmp(cmd[i], "|", ft_strlen(cmd[i]))))
			return (perror_msg(": syntax error near unexpected token\n", NULL),
				params->last_exit_code = 2);
		else if (check_exclamation(cmd[i], params) && cmd[i + 1] == NULL
			&& !cmd[i - 1])
			return (1);
		else if ((i == 0 && (!ft_strncmp(cmd[i], "|", 2) || !ft_strncmp(cmd[i],
						"||", 3))) || (i > 0 && !ft_strncmp(cmd[i], "|", 1)
				&& cmd[i + 1] == NULL) || (isoperators(cmd[i])
				&& (ft_strlen(cmd[i]) > 2 || cmd[i][1] == '|')))
			return (perror_msg(": syntax error near unexpected token\n", NULL),
				params->last_exit_code = 2);
		i++;
	}
	return (0);
}

int	check_general_errors(char *new_input, char **cmd, t_params *params)
{
	if (!new_input || !params)
		return (0);
	else if (check_return_zero(new_input, params))
	{
		free(new_input);
		return (1);
	}
	else if (check_error_pipe(cmd, params))
	{
		free(new_input);
		free_array(params->parsed);
		return (1);
	}
	return (0);
}
