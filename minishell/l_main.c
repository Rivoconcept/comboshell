/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:33:58 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/18 15:05:19 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_cmd *current;
    char *input;
    int rank_cmd;
    int i;
    int status = 0;
    t_node *node;
    t_params *params = create_list_params(envp);
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

    params->status = 0;
    (void)argc;
    char *temp;

    while (1)
    {
        rank_cmd = 1;
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
                argv = put_argv(input, params);
                free(input);
                input = join_argv(argv);
                free(argv);
                params->cmd = return_commands(input, params);
                current = params->cmd;
                while (current != NULL)
                {
                    temp = join_argv(current->cmd);
                    process_here(&temp, here_key(temp), rank_cmd);
                    rank_cmd++;
                    free(temp);
                    current = current->next;
                }
                current = params->cmd;
                while (current != NULL)
                {
                    if(check_infile(current->cmd) == 0)
                        break;
                    current = current->next;
                }
               
                while (has_next(input, &i))
                    node = parse(input, &i);
                if (node)
                {
                    exec(node, input, params);
                    node_drop(node);
                }
                
                
                add_history(input);
            }
        }
        free(input);
    }
    return status;
}

