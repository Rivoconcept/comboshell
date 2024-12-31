/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:38:41 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/31 17:52:17 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_head_with_next(t_params *params, t_cmd *current,
		t_cmd *node_to_delete)
{
	params->command = node_to_delete->next;
	params->command->next = NULL;
	free_cmd_fields(current);
	free(current);
	free_cmd_fields(node_to_delete);
	free(node_to_delete);
}

int	check_less(t_params *params)
{
	t_cmd	*current;

	current = params->command;
	while (current != NULL)
	{
		if (current->flag_less)
			return (1);
		current = current->next;
	}
	return (0);
}

int	check_infile(t_cmd *current)
{
	struct stat	statbuf;
	int			i;

	i = 0;
	while (current->cmd[i] != NULL)
	{
		if (ft_strcmp(current->cmd[i], "<") == 0)
		{
			if (stat(current->cmd[++i], &statbuf) != 0)
			{
				current->flag_less = 1;
				perror_msg(": No such file or directory\n", current->cmd[i]);
				return (127);
			}
		}
		i++;
	}
	return (0);
}

void	manage_less(t_params *params)
{
	t_cmd	*current;

	current = params->command;
	while (current != NULL)
	{
		check_infile(current);
		current = current->next;
	}
}