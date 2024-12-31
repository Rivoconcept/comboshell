/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:23:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 12:54:29 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd(t_cmd **cmd, char ***temp)
{
	reset_cmd_flags(*cmd);
	if (*temp)
		free(*temp);
}

t_cmd	*init_command(char **argv)
{
	t_cmd	*cmd;
	char	**temp;
	int		var[3];

	cmd = NULL;
	temp = NULL;
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	while (argv[var[0]] != NULL)
	{
		if (ft_strcmp(argv[var[0]], "|") == 0)
		{
			if (add_separator(var, &temp, cmd, argv))
				return (NULL);
		}
		else
		{
			if (initialize_cmd(var, &temp, cmd, argv))
				return (NULL);
			check_end_cmd(var, &temp, &cmd, argv);
		}
		var[0]++;
	}
	return (clean_cmd(&cmd, &temp), cmd);
}

void	free_command(t_cmd *command)
{
	int	i;

	if (!command)
		return ;
	if (command->cmd)
	{
		i = 0;
		while (command->cmd[i])
		{
			free(command->cmd[i]);
			command->cmd[i] = NULL;
			i++;
		}
		free(command->cmd);
		command->cmd = NULL;
	}
	free(command);
	command = NULL;
}

void loop_list_cmd(t_cmd **current, t_cmd *to_remove, t_cmd **prev)
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
