/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_cmd_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:16:23 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/26 16:12:29 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_new_list_cmd(char **argv)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (perror("malloc"), NULL);
	new_cmd->cmd = argv;
	new_cmd->next = NULL;
	new_cmd->previous = NULL;
	return (new_cmd);
}

t_cmd	*add_command(t_cmd *command, char **argv)
{
	t_cmd	*new_cmd;
	t_cmd	*current;

	new_cmd = create_new_list_cmd(argv);
	if (!new_cmd)
		return (free_list_cmd(command), NULL);
	if (!command)
		return (new_cmd);
	current = command;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
	new_cmd->previous = current;
	return (command);
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
	params->new_input = NULL;
	params->parsed = NULL;
	while (envp[i])
	{
		if (!create_env(&params->myenvp, envp[i]))
			return (cleanup_and_exit(params, 1), NULL);
		if (!create_export(&params->myexport, envp[i]))
			return (cleanup_and_exit(params, 1), NULL);
		i++;
	}
	return (params);
}
