/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 09:33:58 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 18:41:14 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
    char *input;

    rl_catch_signals = 0;
    signal_handlers(SIGCHLD);
    signal_handlers(SIGINT);
    signal_handlers(SIGQUIT);
    t_params *params;

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
        input = readline("# ");
        if (!input)
        {
             rl_clear_history();
            break;
        }
        if (*input) {
            if(input[ft_strlen(input) - 1] == '\\' || check_quote(input) == 1)
                multiline(&input);
            process_here(here_key(input));
            argv = put_argv(argv, input, params);
            int i = 0;
            while (argv[i] != NULL)
            {
                printf("%s\n", argv[i]);
                i++;
            }
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

