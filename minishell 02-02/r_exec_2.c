/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 21:26:03 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd_not_found(t_params *params, char *cmd)
{
	if (!isbuiltins(cmd))
	{
		if (cmd == NULL)
			return (1);
		if (is_operator(cmd[0]))
		{
			perror_msg(cmd,
				": syntax error near unexpected symbol or newline\n");
			params->last_exit_code = 2;
			return (1);
		}
		params->last_exit_code = check_path(cmd, params);
		if (params->last_exit_code != 0)
			return (params->last_exit_code);
	}
	return (0);
}

void	exec_child(t_params *params, t_cmd *current, int fd[2])
{
	close(params->fd_in);
	close(params->fd_out);
	if (params->prev_pipe_read != -1)
	{
		dup2(params->prev_pipe_read, STDIN_FILENO);
		close(params->prev_pipe_read);
	}
	if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	signal(SIGQUIT, SIG_DFL);
	input_r(current, params->rank_cmd, params, 1);
	output(current, params);
	exec_child_builtins(params, current);
	if (check_cmd_not_found(params, current->cmd[0]))
		cleanup_and_exit(params, params->last_exit_code);
	if (execve(current->cmd[0], current->cmd, params->envp) == -1)
	{
		perror_msg(": command not found\n", NULL);
		cleanup_and_exit(params, 127);
	}
}

void	exec_child_process(t_params *params, t_cmd *current, int tab, int fd[2])
{
	if (params->pid_tab[tab] == 0)
	{
		exec_child(params, current, fd);
	}
	else
	{
		if (params->prev_pipe_read != -1)
			close(params->prev_pipe_read);
		if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
		{
			close(fd[1]);
			params->prev_pipe_read = fd[0];
		}
		else
		{
			params->prev_pipe_read = -1;
		}
	}
}

int	call_exec_builtins(t_params *params)
{
	t_cmd	*current;

	current = params->command;
	if (current && current->cmd && current->cmd[0] && current->cmd[0][0] != '\0'
		&& isbuiltins(current->cmd[0]) && current->next == NULL)
	{
		exec_builtins(params, current);
		current = current->next;
		return (1);
	}
	return (0);
}

void	check_pipe_error(t_cmd *current, int fd[2], t_params *params)
{
	if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			if (params->prev_pipe_read != -1)
				close(params->prev_pipe_read);
			free(params->pid_tab);
			cleanup_and_exit(params, EXIT_FAILURE);
		}
	}
}
