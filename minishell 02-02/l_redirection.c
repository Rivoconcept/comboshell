/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:20:34 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/30 21:39:34 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_red(t_params *params)
{
	int		rank_cmd;
	t_cmd	*current;
	t_cmd	*next;

	rank_cmd = 0;
	current = params->command;
	while (current != NULL)
	{
		next = current->next;
		del_in(current, rank_cmd);
		rank_cmd++;
		current = next;
	}
	free_commands_and_nodes_if_empty(params);
	current = params->command;
	while (current != NULL)
	{
		next = current->next;
		del_out(current);
		current = next;
	}
	free_commands_and_nodes_if_empty(params);
}

static void	handle_here_input(int num_cmd, t_params *params, int child)
{
	char	*file;
	int		fd_in;

	file = prepare_temp_file(num_cmd);
	fd_in = open_input_here(file, params, O_RDONLY, child);
	if (fd_in >= 0)
	{
		dup2_stdin(fd_in, file);
		unlink(file);
		if (fd_in >= 0)
			close(fd_in);
	}
	free(file);
}

void	input_r(t_cmd *current, int num_cmd, t_params *params, int child)
{
	int	fd_in;

	if (current->here >= 0 || current->less)
	{
		if (current->less && (current->here < 0
				|| current->rank_here < current->rank_less))
		{
			fd_in = open_input_file(current->less, params, O_RDONLY, child);
			if (fd_in >= 0)
			{
				dup2_stdin(fd_in, current->less);
				if (fd_in >= 0)
					close(fd_in);
			}
		}
		else if (current->here >= 0)
			handle_here_input(num_cmd, params, child);
	}
}

void	output(t_cmd *current, t_params *params)
{
	int	fd_out;

	if (current->great || current->dgreat)
	{
		if (current->great && (!current->dgreat
				|| current->rank_dgreat < current->rank_great))
		{
			fd_out = open_file(current->great, params,
					O_WRONLY | O_CREAT | O_TRUNC);
			handle_fd_out(fd_out, current->great);
		}
		else if (current->dgreat)
		{
			fd_out = open_file(current->dgreat, params,
					O_WRONLY | O_CREAT | O_APPEND);
			handle_fd_out(fd_out, current->dgreat);
		}
	}
}
