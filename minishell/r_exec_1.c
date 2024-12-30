/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/30 11:37:59 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	ft_get_pid_nbr(t_params *params)
{
	int		nbr;
	t_cmd	*current;

	current = params->command;
	nbr = 0;
	while (current != NULL)
	{
		if (ft_strncmp(current->cmd[0], "|", 1) == 0)
		{
			current = current->next;
			continue ;
		}
		current = current->next;
		nbr++;
	}
	return (nbr);
}

void	exec_builtins(t_params *params, t_cmd *current)
{
	input_r(current, params->rank_cmd, params, 0);
	output(current, params);
	params->last_exit_code = run_builtins(current->cmd, params);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
}

int	ft_check_continue(t_params *params, t_cmd **current)
{
	if (!ft_strcmp((*current)->cmd[0], "|"))
	{
		(*current) = (*current)->next;
		params->rank_cmd++;
		return (1);
	}
	return (0);
}

void	check_fork_error(t_params *params, t_cmd *current, int tab, int fd[2])
{
	if (params->pid_tab[tab] == -1)
	{
		perror("fork");
		if (params->prev_pipe_read != -1)
			close(params->prev_pipe_read);
		if (current->next)
		{
			close(fd[0]);
			close(fd[1]);
		}
		cleanup_and_exit(params, EXIT_FAILURE);
	}
}

void	exec_child_builtins(t_params *params, t_cmd *current)
{
	if (isbuiltins(current->cmd[0]))
	{
		run_builtins(current->cmd, params);
		cleanup_and_exit(params, params->last_exit_code);
	}
}
