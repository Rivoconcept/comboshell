/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_test_error_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:17:00 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 16:33:07 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isoperators(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0' && is_operator(cmd[i]))
		i++;
	if (cmd[i] == '\0')
		return (1);
	return (0);
}

int	check_return_zero(char *input, t_params *params)
{
	int	i;

	if (!input || !params)
		return (0);
	i = 0;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (input[i] == '\0' || input[i] == ':')
	{
		params->last_exit_code = 0;
		return (1);
	}
	return (0);
}

int	isspecialc(char *input, t_params *params)
{
	int	i;

	if (!input || !params)
		return (0);
	i = 0;
	while (input[i] && ft_is_space(input[i]))
		i++;
	if (input[i] == '!')
	{
		params->last_exit_code = 1;
		return (1);
	}
	return (0);
}

int	first_error_checking(char *input, t_params *params)
{
	if (check_unmatched_quotes(input))
	{
		perror_msg("error: unmatched quotes found\n", NULL);
		params->last_exit_code = 1;
		free(input);
		return (1);
	}
	return (0);
}
