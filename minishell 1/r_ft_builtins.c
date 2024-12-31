/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:57:46 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:50:27 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltins(char *command)
{
	int		i;
	char	*builtins[8];

	if (!command || command == NULL)
		return (0);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i] != NULL)
	{
		if (!ft_strncmp(command, builtins[i], ft_strlen(builtins[i]))
			&& ft_strlen(command) == ft_strlen(builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

int	cmd_not_found(t_params *params)
{
	t_cmd	*current;

	current = params->command;
	if (!current->cmd || !current->cmd[0])
		return (0);
	while (current != NULL && !isbuiltins(current->cmd[0]))
	{
		if (access(current->cmd[0], X_OK | F_OK) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

int	run_builtins(char **cmd, t_params *params)
{
	if (!cmd || !cmd[0])
		return (0);
	if (!ft_strcmp(cmd[0], "cd"))
		params->last_exit_code = ft_cd(cmd[1], params);
	else if (!ft_strcmp(cmd[0], "pwd"))
		params->last_exit_code = ft_pwd(params);
	else if (!ft_strcmp(cmd[0], "env"))
		params->last_exit_code = ft_env(params);
	else if (!ft_strcmp(cmd[0], "echo"))
		params->last_exit_code = ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		params->last_exit_code = ft_unset(cmd, params);
	else if (!ft_strcmp(cmd[0], "export"))
		params->last_exit_code = ft_export(cmd, params);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd, params);
	return (params->last_exit_code);
}
