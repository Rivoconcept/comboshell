/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/16 17:21:58 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void register_child(t_children *children, pid_t pid)
{
    if (children->count < MAX_CHILDREN) {
        children->pids[children->count++] = pid;
    }
}

void terminate_children(t_children *children)
{
    int i;

    i = 0;
    while (i < children->count)
    {
        if (children->pids[i] > 0)
            kill(children->pids[i], SIGKILL);
        i++;
    }
    children->count = 0;
}*/


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