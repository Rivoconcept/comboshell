/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_utils_8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/30 20:11:18 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_empty_command(t_params *params, t_cmd *current, t_cmd *next,
		t_cmd *previous)
{
	t_cmd	*node_to_delete;

	if (next && next->cmd && ft_strcmp(next->cmd[0], "|") == 0)
	{
		node_to_delete = next;
		if (current == params->command && node_to_delete->next)
			handle_head_with_next(params, current, node_to_delete);
		else if (current == params->command && !node_to_delete->next)
			handle_head_without_next(params, current, node_to_delete);
		else if (current != params->command && node_to_delete->next)
			handle_middle_with_next(current, node_to_delete);
		else if (current != params->command && !node_to_delete->next)
			handle_middle_without_next(current, node_to_delete, previous);
	}
	else if (!next)
	{
		handle_end_node(params, current, previous);
	}
}

void	free_commands_and_nodes_if_empty(t_params *params)
{
	t_cmd	*current;
	t_cmd	*next;
	t_cmd	*previous;

	if (params == NULL || params->command == NULL)
		return ;
	current = params->command;
	while (current)
	{
		next = current->next;
		previous = current->previous;
		if (current->cmd == NULL)
		{
			handle_empty_command(params, current, next, previous);
			current = params->command;
		}
		else
			current = next;
	}
}
