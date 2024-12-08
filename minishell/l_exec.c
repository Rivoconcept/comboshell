/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:01:52 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/08 15:27:25 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void print_argv(char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }

}

static void input_r(t_redirections *redirs) {
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

static void output(t_redirections *redirs) {
    int fd_out;
    
    if (redirs->great || redirs->dgreat) {
        if(redirs->great)
        {
            printf("great\n");
            fd_out = open(redirs->great->value, O_WRONLY | O_CREAT | O_APPEND , 0644);

        }
        if(redirs->dgreat)
        {
            printf("degreat\n");
            fd_out = open(redirs->dgreat->value, O_WRONLY | O_CREAT | O_TRUNC , 0644);
        }
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

static void pipet_fd(int i, int num_cmds, int **pipes, t_redirections *redirs) {
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

static void execute_command(t_element *cmd, int **pipes, int i, int num_cmds, t_params *params)
{
    char **argv = NULL;
    pid_t pid;
    t_element *commande;
    t_redirections redirs = {NULL, NULL, NULL, NULL};

    argv = put_argv(cmd->value, params);
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
        input_r(&redirs);
        output(&redirs);
        pipet_fd(i, num_cmds, pipes, &redirs);
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

static void execute_dynamic_pipeline(t_element *cmd, char *input, t_params *params) {
    int num_cmds;
    int **pipes = NULL;
    int i;
    int fd_oout = dup(1);
    int fd_oin = dup(0);
    t_element *current_cmd;
    char **r_cmd;
    t_redirections redirs = {NULL, NULL, NULL, NULL};

    num_cmds = count_elements(cmd);
    if (num_cmds == 0) return;
    r_cmd = ft_split(cmd->value, ' ');
    if (num_cmds == 1 && isbuiltins(r_cmd[0]))
    {
        current_cmd = parse_cmd(cmd->value);
        cmd = redirect_io(&current_cmd, &redirs);
        free_array(r_cmd);
        r_cmd = list_to_array(cmd);
        free_elements(cmd);
        input_r(&redirs);
        output(&redirs);
        print_argv(r_cmd);
        run_builtins(r_cmd, params, input);
        
    }
    else {
        pipes = create_pipes(num_cmds - 1);
        current_cmd = cmd;
        i = 0;
        while (current_cmd) {
            execute_command(current_cmd, pipes, i, num_cmds, params);
            current_cmd = current_cmd->next;
            i++;
        }
        if (num_cmds > 1)
            close_pipes(pipes, num_cmds - 1);
        wait_for_children(num_cmds);
    }
    dup2(fd_oin, STDIN_FILENO);
    dup2(fd_oout, STDOUT_FILENO);
        
}

int exec(const t_node *node, char *input, t_params *params) {
    t_element *commands = NULL;

    node_list(node, &commands);
    execute_dynamic_pipeline(commands, input, params);
    free_elements(commands);
    unlink(PID_FILE);
    return 1;
}