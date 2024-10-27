/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:33:58 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/08 09:33:58 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *input;
    char **path;
    char **keys;
    int i;

    rl_catch_signals = 0;
    signal_handlers(SIGCHLD);
    signal_handlers(SIGINT);
    signal_handlers(SIGQUIT);
    while (1)
    {
        i = 0;
        input = readline("# ");
        if (!input)
        {
             rl_clear_history();
            break;
        }
        if (*input) {
            if(input[ft_strlen(input) - 1] == '\\' || check_quote(input) == 1)
                multiline(&input);
            process_here(&input, here_key(input));
            while (has_next(input, &i)) {
                s_node *node = parse(input, &i);
                exec(node);
                node_drop(node);
            }
            add_history(input);
        }
        free(input);
    }

    return 0;
}

