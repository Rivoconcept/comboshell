/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:11:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 11:11:18 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void register_child(t_children *children, pid_t pid)
{
    if (children->count < MAX_CHILDREN) {
        children->pids[children->count++] = pid;
    }
}

void terminate_children(t_children *children)
{
    for (int i = 0; i < children->count; i++) {
        if (children->pids[i] > 0)
            kill(children->pids[i], SIGKILL);
    }
    children->count = 0;
}


void sig_handler(int signal)
{
    if (signal == SIGINT) {
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
    sigaction(sign, &s_act, NULL);
}