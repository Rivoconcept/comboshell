/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:33:58 by rrakoton          #+#    #+#             */
/*   Updated: 2024/11/25 14:22:50 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int main(int argc, char *argv[])
{
    char *input;
    int i;
    int status = 0;
    t_node *node;
    t_params *params;
    (void)argv;

    rl_catch_signals = 0;

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = catch_ctrl_c;
    sigaction(SIGINT, &sa, NULL);

    memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = catch_sigquit;
    sigaction(SIGQUIT, &sa, NULL);

    params = (t_params *)malloc(sizeof(t_params));
    if (!params)
    {
        perror("Failed to allocate memory for params");
        exit(EXIT_FAILURE);
    }
    params->status = 0;
    (void)argc;

    while (1)
    {
        i = 0;
        input = readline("# ");
        if (!input)
        {
            rl_clear_history();
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        if (*input)
        {
            if (ft_strlen(input) > 0)
            {
                params->cmd = put_argv(input, params);
                free(input);
                input = join_argv(argv);
                free(argv);
                while (has_next(input, &i))
                    node = parse(input, &i);
                if (node)
                {
                    exec(node);
                    node_drop(node);
                }
                add_history(input);
            }
        }
        free(input);
    }
    
    return status;
}

