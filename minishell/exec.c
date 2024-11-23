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

static void input(s_redirections *redirs) {
    int fd_in;
    if (redirs->less) {
        fd_in = open(redirs->less->value, O_RDONLY);
        if (fd_in == -1) {
            perror("open failed");
            exit(1);
        }
        if (dup2(fd_in, STDIN_FILENO) == -1) {
            perror("dup2 failed");
            close(fd_in);
            exit(1);
        }
        close(fd_in);
    }
}

static void output(s_redirections *redirs) {
    int fd_out;
    if (redirs->great || redirs->dgreat) {
        if(redirs->great)
            fd_out = open(redirs->great->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if(redirs->dgreat)
            fd_out = open(redirs->dgreat->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_out == -1) {
            perror("open failed");
            exit(1);
        }
        if (dup2(fd_out, STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            close(fd_out);
            exit(1);
        }
        close(fd_out);
    }
}

static void pipes_fd(int i, int num_cmds, int **pipes, s_redirections *redirs) {
    if (i > 0 && !redirs->less) {
        if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1) {
            perror("dup2 failed");
            exit(1);
        }
    }
    if (i < num_cmds - 1 && !redirs->great && !redirs->dgreat) {
        if (dup2(pipes[i][1], STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            exit(1);
        }
    }
}

static void execute_command(s_element *cmd, int **pipes, int i, int num_cmds)
{
    char **argv = NULL;
    pid_t pid;
    s_element *commande;
    s_redirections redirs = {NULL, NULL, NULL, NULL};

    argv = put_argv(argv, cmd->value, NULL);
    free(cmd->value);
    cmd->value  = join_argv(argv);
    free(argv);

    commande = parse_cmd(cmd->value);
    cmd = redirect_io(&commande, &redirs);
    argv = list_to_array(cmd);
    free_elements(commande);

    pid = fork();
    if (pid == -1)
    {
        perror("fork failed");
        ft_free(argv, count_array(argv));
        free_redirections(&redirs);
        exit(1);
    }
    if (pid == 0)
    {
        write_pid(getpid());
        input(&redirs);
        output(&redirs);
        pipes_fd(i, num_cmds, pipes, &redirs);
        free_redirections(&redirs);
        close_pipes(pipes, num_cmds - 1);
        if (execvp(argv[0], argv) == -1) {
            perror("execvp failed");
            exit(1);
        }
    }
   ft_free(argv, count_array(argv));
   free_redirections(&redirs);
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