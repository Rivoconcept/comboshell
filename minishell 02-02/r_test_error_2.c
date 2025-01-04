/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:03:19 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/04 13:59:52 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_op(char **cmd, int i)
{
	if (cmd[i] && cmd[i + 1] && is_pipe(cmd[i]) && isoperator(cmd[i + 1])
		&& !is_pipe(cmd[i + 1]))
		return (0);
	if (isoperators(cmd[i]) && ft_strlen(cmd[i]) > 2)
		return (1);
	if (isoperator(cmd[i]))
	{
		if (cmd[i + 1] == NULL)
			return (1);
		if (isoperator(cmd[i + 1]))
			return (1);
	}
	if (is_pipe(cmd[i]))
	{
		if (i == 0 || cmd[i + 1] == NULL)
			return (1);
	}
	return (0);
}

int	check_error_pipe(char **cmd, t_params *params)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (cmd[i] == NULL || cmd[i][0] == '\0')
		{
			perror_msg(NULL, ": command not found\n");
			return (params->last_exit_code = 127);
		}
		if (check_return_zero(cmd[i], params))
			return (1);
		else if (isspecialc(cmd[i], params) && cmd[i + 1] == NULL \
			&& !cmd[i - 1])
			return (1);
		else if (check_error_op(cmd, i))
		{
			perror_msg(NULL, ": syntax error near unexpected token\n");
			params->last_exit_code = 2;
			return (1);
		}
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
