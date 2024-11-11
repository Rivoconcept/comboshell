/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:01:52 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/26 07:01:52 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_command(s_element *cmd, int **pipes, int i, int num_cmds)
{
    char **argv = NULL;
    pid_t pid;
    s_element *commande;

    argv = put_argv(argv, cmd->value, NULL);
    free(cmd->value);
    cmd->value  = join_argv(argv);
    free(argv);

    commande = parse_cmd(cmd->value);
    argv = list_to_array(commande);
    free_elements(commande);

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        ft_free(argv, count_array(argv));
        exit(1);
    }
    if (pid == 0)
    {
        write_pid(getpid());
        if (i > 0)
            dup2(pipes[i - 1][0], STDIN_FILENO);
        if (i < num_cmds - 1)
            dup2(pipes[i][1], STDOUT_FILENO);
        close_pipes(pipes, num_cmds - 1);
        if (execvp(argv[0], argv) == -1) {
            perror("execvp failed");
            exit(1);
        }
    }
   ft_free(argv, count_array(argv));
}

static void execute_dynamic_pipeline(s_element *cmd) {
    int num_cmds;
    int **pipes = NULL;
    int i;
    s_element *current_cmd;

    num_cmds = count_elements(cmd);
    if (num_cmds == 0) return;
    if (num_cmds > 1)
        pipes = create_pipes(num_cmds - 1);
    current_cmd = cmd;
    i = 0;
    while (current_cmd) {
        execute_command(current_cmd, pipes, i, num_cmds);
        current_cmd = current_cmd->next;
        i++;
    }
    if (num_cmds > 1)
        close_pipes(pipes, num_cmds - 1);
    wait_for_children(num_cmds);
}

int exec(const s_node *node) {
    s_element *commands = NULL;

    node_list(node, &commands);
    execute_dynamic_pipeline(commands);
    free_elements(commands);
    unlink(PID_FILE);
    return 1;
}