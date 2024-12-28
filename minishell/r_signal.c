/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/27 14:57:57 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
pid_t	g_sig_num = 0;
void	sig_handler(int signal)
{
	int fd[2];
	
	pipe(fd);
	if (signal == SIGINT)
	{
		write(fd[1], "\n", 1);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		rl_replace_line("", 0);
		close(fd[0]);
		g_sig_num = SIGINT;
		/*write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();*/
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
