/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_utils_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:04:52 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/30 20:04:52 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_head_without_next(t_params *params, t_cmd *current,
		t_cmd *node_to_delete)
{
	params->command = node_to_delete;
	params->command->next = NULL;
	free_cmd_fields(current);
	free(current);
}

void	handle_middle_with_next(t_cmd *current, t_cmd *node_to_delete)
{
	if (current->previous)
	{
		current->previous->next = node_to_delete->next;
	}
	if (node_to_delete->next)
	{
		node_to_delete->next->previous = current->previous;
	}
	free_cmd_fields(current);
	free(current);
	free_cmd_fields(node_to_delete);
	free(node_to_delete);
}

void	handle_middle_without_next(t_cmd *current, t_cmd *node_to_delete,
		t_cmd *previous)
{
	previous->next = NULL;
	free_cmd_fields(current);
	free(current);
	free_cmd_fields(node_to_delete);
	free(node_to_delete);
}

static void	free_current_previous(t_cmd *current, t_cmd *previous)
{
	if (current)
	{
		free_cmd_fields(current);
		free(current);
	}
	if (previous)
	{
		free_cmd_fields(previous);
		free(previous);
	}
}

void	handle_end_node(t_params *params, t_cmd *current, t_cmd *previous)
{
	t_cmd	*node_to_delete;

	if (current == params->command)
	{
		free_cmd_fields(current);
		free(current);
		params->command = NULL;
	}
	else if (previous && ft_strcmp(previous->cmd[0], "|") == 0
		&& previous->previous)
	{
		node_to_delete = previous->previous;
		if (node_to_delete)
		{
			node_to_delete->next = NULL;
		}
		free_current_previous(current, previous);
	}
	else if (previous && ft_strcmp(previous->cmd[0], "|") == 0
		&& !previous->previous)
	{
		previous->next = NULL;
		free_cmd_fields(current);
		free(current);
	}
}
