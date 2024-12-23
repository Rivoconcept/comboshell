/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/23 11:42:00 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        g_sig_num = SIGINT;
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void signal_handlers(int sign)
{
    struct sigaction s_act;

    ft_memset(&s_act, 0, sizeof(s_act));
    s_act.sa_handler = sig_handler;
    sigemptyset(&s_act.sa_mask);
    s_act.sa_flags = SA_RESTART;
    sigaction(sign, &s_act, NULL);
}