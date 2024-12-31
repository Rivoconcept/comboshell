/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 18:10:11 by rhanitra         ###   ########.fr       */
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
		return ;
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
