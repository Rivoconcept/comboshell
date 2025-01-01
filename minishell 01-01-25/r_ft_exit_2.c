/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_exit_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:48:59 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:49:57 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clean_arg(char *arg)
{
	char	*temp;

	temp = ft_strtrim(arg, "\t\n\v\f\r ");
	if (is_numeric(temp))
	{
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int	ft_exit(char **parsed, t_params *params)
{
	unsigned long long	value;
	unsigned long long	res;
	long long			exit_code;

	if (check_errors_exit(parsed, params))
		return (1);
	value = (unsigned long long)INT64_MAX;
	if (parsed[1][0] == '-')
		value = ((unsigned long long)INT64_MAX) + 1;
	res = ft_atoi_ull(parsed[1]);
	if (res > value)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		write(STDERR_FILENO, "minishell: exit:", ft_strlen("minishell: exit:"));
		write(STDERR_FILENO, parsed[1], ft_strlen(parsed[1]));
		write(STDERR_FILENO, ": numeric argument required\n",
			ft_strlen(": numeric argument required\n"));
		cleanup_and_exit(params, 2);
	}
	exit_code = ft_atoi_lld(parsed[1]);
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	cleanup_and_exit(params, (unsigned char)exit_code);
	return (0);
}
