/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/30 13:10:22 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

void	wait_pid(t_params *params, t_cmd *current, int status)
{
	int	tab;

	tab = 0;
	while (current != NULL)
	{
		if (!ft_strcmp(current->cmd[0], "|"))
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
				printf("Quit (core dumped)\n");
			else if (WTERMSIG(status) == SIGINT)
				params->last_exit_code = 128 + WTERMSIG(status);
			else
				params->last_exit_code = 128 + WTERMSIG(status);
		}
		current = current->next;
		tab++;
	}
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
	if (call_exec_builtins(params))
	{
		;
	}
	else
	{
		ft_handle_child(params);
		wait_pid(params, params->command, status);
	}
	free(params->pid_tab);
	dup2(params->fd_in, STDIN_FILENO);
	dup2(params->fd_out, STDOUT_FILENO);
}
