/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 09:46:49 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	ft_handle_child(t_params *params)
{
	int		fd[2];
	t_cmd	*current;
	int		tab;

	current = params->command;
	tab = 0;
	while (current != NULL)
	{
		if (ft_check_continue(params, &current) == 1)
			continue ;
		check_pipe_error(current, fd, params);
		params->pid_tab[tab] = fork();
		check_fork_error(params, current, tab, fd);
		exec_child_process(params, current, tab, fd);
		tab++;
		params->rank_cmd++;
		current = current->next;
		if (current && !ft_strcmp(current->cmd[0], "|"))
		{
			params->rank_cmd++;
			current = current->next;
		}
	}
}

void	wait_pid(t_params *params, t_cmd *current, int status)
{
	int	tab;

	tab = 0;
	while (current != NULL)
	{
		if (params && current->cmd[0] && !ft_strcmp(current->cmd[0], "|"))
		{
			current = current->next;
			continue ;
		}
		waitpid(params->pid_tab[tab], &status, 0);
		if (WIFEXITED(status))
			params->last_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				perror_msg(": Quit (core dumped)\n", NULL);
			params->last_exit_code = 128 + WTERMSIG(status);
		}
		current = current->next;
		tab++;
	}
}
int builtins_execution(t_params *params)
{
	if (call_exec_builtins(params))
	{
		if (params->pid_tab)
			free(params->pid_tab);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_params *params)
{
	int	status;

	status = 0;
	if (params->envp)
		free_array(params->envp);
	params->envp = put_envp(params);
	params->pid_tab = malloc(sizeof(pid_t) * ft_get_pid_nbr(params));
	if (!params->pid_tab)
	{
		perror("malloc");
		cleanup_and_exit(params, EXIT_FAILURE);
	}
	ft_memset(params->pid_tab, 0, sizeof(pid_t) * ft_get_pid_nbr(params));
	if (builtins_execution(params))
		return ;
	else
	{
		ft_handle_child(params);
		wait_pid(params, params->command, status);
	}
	free(params->pid_tab);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
}
