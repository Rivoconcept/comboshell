/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:16:23 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 21:39:40 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	format_cmd(t_params *params)
{
	t_cmd	*current;
	char	*cmd;

	current = params->command;
	while (current != NULL)
	{
		if (current->cmd[0] && ft_strncmp(current->cmd[0], "|", 1) == 0)
		{
			current = current->next;
			continue ;
		}
		if (current->cmd[0] && !isbuiltins(current->cmd[0]))
		{
			if (find_char(current->cmd[0], ' '))
				reformat_cmd(&current);
			cmd = check_cmd_standard(params, current->cmd[0]);
			if (check_error_command(params, &current, cmd))
				return (1);
		}
		current = current->next;
	}
	return (0);
}

int	create_env_and_export(char *input, t_params *params)
{
	if (!create_env(&params->myenvp, input))
	{
		cleanup_and_exit(params, 1);
		return (1);
	}
	if (!create_export(&params->myexport, input))
	{
		cleanup_and_exit(params, 1);
		return (1);
	}
	return (0);
}

t_params	*create_list_params(char **envp)
{
	int			i;
	t_params	*params;

	i = 0;
	params = malloc(sizeof(t_params));
	if (!params)
		return (perror("malloc"), NULL);
	params->myenvp = NULL;
	params->myexport = NULL;
	params->command = NULL;
	params->envp = NULL;
	params->pid_tab = NULL;
	params->prev_pipe_read = -1;
	params->rank_cmd = 0;
	params->last_exit_code = 0;
	params->flag_env = 0;
	params->new_input = NULL;
	params->parsed = NULL;
	while (envp[i])
	{
		if (create_env_and_export(envp[i], params))
			return (NULL);
		i++;
	}
	return (params);
}

void	delete_null_in_argv(t_params *params)
{
	int		i;
	int		j;
	t_cmd	*current;

	current = params->command;
	while (current != NULL)
	{
		i = 0;
		while (current->cmd[i] != NULL)
		{
			if (current->cmd[i][0] == '\0')
			{
				free(current->cmd[i]);
				j = i;
				while (current->cmd[j] != NULL)
				{
					current->cmd[j] = current->cmd[j + 1];
					j++;
				}
				continue ;
			}
			i++;
		}
		current = current->next;
	}
}
