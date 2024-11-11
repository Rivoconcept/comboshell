/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:50:53 by rrakoton          #+#    #+#             */
/*   Updated: 2024/11/08 15:50:53 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void node_list(const s_node *node, s_element **elements)
{
    if (node->type == PAIR_NODE) {
        node_list(node->data.pair.left, elements);
        node_list(node->data.pair.right, elements);
    } else if (node->type == STR_NODE)
    {
        *elements = add_element(*elements, node->data.str, 0);
    }
}

void wait_for_children(int num_cmds)
{
    int i;

    i = 0;
    while (i < num_cmds)
    {
        wait(NULL);
        i++;
    }
}

void close_pipes(int **pipes, int num_pipes)
{
    int i;

    i = 0;
    while (i < num_pipes)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
        i++;
    }
    free(pipes);
}

int **create_pipes(int num_pipes)
{
    int i;
    int **pipes;
    
    i= 0;
    pipes = malloc(num_pipes * sizeof(int*));
    while (i < num_pipes)
    {
        pipes[i] = malloc(2 * sizeof(int));
        if (pipe(pipes[i]) == -1)
        {
            perror("pipe failed");
            exit(1);
        }
        i++;
    }
    return pipes;
}
