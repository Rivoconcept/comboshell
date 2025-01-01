/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_cmd_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:23:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 18:29:18 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_list_cmd(t_cmd **current, t_cmd *to_remove, t_cmd **prev)
{
	while ((*current) && (*current) != to_remove)
	{
		(*prev) = (*current);
		(*current) = (*current)->next;
	}
}

t_cmd	*remove_element_cmd(t_cmd *head, t_cmd *to_remove)
{
	t_cmd	*current;
	t_cmd	*prev;

	current = head;
	prev = NULL;
	if (!head || !to_remove)
		return (head);
	if (head == to_remove)
	{
		head = head->next;
		free_command(to_remove);
		to_remove = NULL;
		return (head);
	}
	loop_list_cmd(&current, to_remove, &prev);
	if (current == to_remove)
	{
		prev->next = current->next;
		free_command(current);
		current = NULL;
	}
	return (head);
}

int	delete_cmd_null(t_params *params)
{
	t_cmd	*current;
	t_cmd	*next;

	current = params->command;
	while (current != NULL)
	{
		next = current->next;
		if ((current->cmd && current->cmd[0] && ft_strncmp(current->cmd[0],
					"\0", 1) == 0) && next && next->cmd
			&& ft_strcmp(next->cmd[0], "|") == 0)
		{
			params->command = remove_element_cmd(params->command, current);
			params->command = remove_element_cmd(params->command, next);
			current = params->command;
			continue ;
		}
		current = next;
	}
	return (0);
}
