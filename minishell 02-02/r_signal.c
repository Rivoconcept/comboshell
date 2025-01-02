/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/02 12:14:28 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_sig_num = 0;

int	handle_ctrl_c(t_params *params, char *input)
{
	if (g_sig_num == SIGINT)
	{
		dup2(params->fd_in, STDIN_FILENO);
		free(input);
		g_sig_num = 0;
		params->last_exit_code = 130;
		return (1);
	}
	return (0);
}

void	clean_ctrl_d(char *input, t_params *params)
{
	int	last_exit_status;

	last_exit_status = 0;
	if (!input)
	{
		last_exit_status = params->last_exit_code;
		close(params->fd_in);
		close(params->fd_out);
		printf("exit\n");
		free(input);
		free_list_env(params->myenvp);
		free_list_export(params->myexport);
		free_array(params->envp);
		free(params);
		exit(last_exit_status);
	}
}

int	handle_sigint(t_params *params)
{
	if (g_sig_num == SIGINT)
	{
		g_sig_num = 0;
		dup2(params->fd_in, STDIN_FILENO);
		return (1);
	}
	return (0);
}

void	sig_handler(int signal)
{
	int	fd[2];

	pipe(fd);
	if (signal == SIGINT)
	{
		write(fd[1], "\n", 1);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		rl_replace_line("", 0);
		close(fd[0]);
		g_sig_num = SIGINT;
	}
}

void	signal_handlers(int sign)
{
	struct sigaction	s_act;

	ft_memset(&s_act, 0, sizeof(s_act));
	s_act.sa_handler = sig_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_RESTART;
	sigaction(sign, &s_act, NULL);
}
