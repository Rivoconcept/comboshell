/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:48:59 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/29 17:24:05 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long int	ft_atoi_lld(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

unsigned long long	ft_atoi_ull(const char *str)
{
	int					i;
	unsigned long long	res;

	i = 0;
	res = 0;
	if (!str || !*str)
		return (0);
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

int	check_errors_exit(char **parsed, t_params *params)
{
	if (!parsed[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		cleanup_and_exit(params, params->last_exit_code);
	}
	if (parsed[2])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		write(STDERR_FILENO, "minishell: exit: too many arguments\n",
			ft_strlen("minishell: exit: too many arguments\n"));
		params->last_exit_code = 1;
		return (1);
	}
	if (!is_numeric(parsed[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		write(STDOUT_FILENO, "minishell: exit:", ft_strlen("minishell: exit:"));
		write(STDOUT_FILENO, parsed[1], ft_strlen(parsed[1]));
		write(STDOUT_FILENO, ": numeric argument required\n",
			ft_strlen(": numeric argument required\n"));
		cleanup_and_exit(params, 2);
	}
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
