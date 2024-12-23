/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 18:39:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/22 21:19:02 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void clean_pipe_fd(int ***fd, int pipe_count) {
    int i = 0;
    while(i < pipe_count){
        if ((*fd)[i]) {
            close((*fd)[i][0]);
            close((*fd)[i][1]);
            free((*fd)[i]);
        }
        i++;
    }
    free(*fd);
    *fd = NULL;
}

int put_nbr_pipes(t_cmd *command) {
    int count = 0;
    while (command != NULL) {
        if (!ft_strcmp(command->cmd[0], "|"))
            count++;
        command = command->next;
    }
    return count;
}

void init_pipe_fd(int ***fd, t_params *params) {
    int i = 0;
    int pipe_count = put_nbr_pipes(params->command);
    *fd = malloc(sizeof(int *) * pipe_count);
    if (!*fd) {
        perror("malloc");
        cleanup_and_exit(params, EXIT_FAILURE);
    }
    while(i < pipe_count){
        (*fd)[i] = malloc(sizeof(int) * 2);
        if (!(*fd)[i]) {
            perror("malloc");
            clean_pipe_fd(fd, i);
            cleanup_and_exit(params, EXIT_FAILURE);
        }
        if (pipe((*fd)[i]) == -1) {
            perror("pipe");
            clean_pipe_fd(fd, i);
            cleanup_and_exit(params, EXIT_FAILURE);
        }
        i++;
    }
}

int setup_pipe(int **fd, t_cmd *current, int i) {
    if (current->previous && !ft_strcmp(current->previous->cmd[0], "|")) {
        if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
            return (perror("dup2"), -1);
        close(fd[i - 1][0]);
    }
    if (current->next && !ft_strcmp(current->next->cmd[0], "|")) {
        if (dup2(fd[i][1], STDOUT_FILENO) == -1)
            return (perror("dup2"), -1);
        close(fd[i][1]);
    }
    return 0;
}

void exec_cmd(t_params *params) {
    int nbr_pipes = put_nbr_pipes(params->command);
    int **fd;
    t_cmd *current = params->command;
    pid_t pid;
    int status;
    int i = 0, rank_cmd = 0;

    params->fd_in = dup(STDIN_FILENO);
    params->fd_out = dup(STDOUT_FILENO);

    init_pipe_fd(&fd, params);

    while (current != NULL) {
        if (!ft_strcmp(current->cmd[0], "|")) {
            current = current->next;
            rank_cmd++;
            continue;
        }

        if (isbuiltins(current->cmd[0]) && current->next == NULL) {
            if (setup_pipe(fd, current, i) == -1)
                cleanup_and_exit(params, EXIT_FAILURE);
            input_r(current, rank_cmd);
            output(current);
            params->last_exit_code = run_builtins(current->cmd, params);
            dup2(params->fd_in, STDIN_FILENO);
            dup2(params->fd_out, STDOUT_FILENO);
            if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
                close(fd[i - 1][0]);
            if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
                close(fd[i][1]);
            current = current->next;
            continue;
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            clean_pipe_fd(&fd, nbr_pipes);
            cleanup_and_exit(params, EXIT_FAILURE);
        }

        if (pid == 0) {
            signal(SIGQUIT, SIG_DFL);
            if (setup_pipe(fd, current, i) == -1)
                exit(EXIT_FAILURE);
            input_r(current, rank_cmd);
            output(current);
            clean_pipe_fd(&fd, nbr_pipes);
            if (isbuiltins(current->cmd[0])) {
                params->last_exit_code = run_builtins(current->cmd, params);
                free_list_cmd(params->command);
                cleanup_and_exit(params, params->last_exit_code);
            }
            if (execve(current->cmd[0], current->cmd, params->envp) == -1) {
                perror("execve");
                free_list_cmd(params->command);
                cleanup_and_exit(params, 127);
            }
        } else {
            if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
                close(fd[i - 1][0]);
            if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
                close(fd[i][1]);
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                params->last_exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status)) {
                if (WTERMSIG(status) == SIGQUIT)
                    printf("Quit (core dumped)\n");
                else if (WTERMSIG(status) == SIGINT)
                    params->last_exit_code = 128 + WTERMSIG(status);
                else
                    params->last_exit_code = 128 + WTERMSIG(status);
            }
        }

        if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
            i++;
        rank_cmd++;
        current = current->next;
    }

    clean_pipe_fd(&fd, nbr_pipes);
    dup2(params->fd_in, STDIN_FILENO);
    dup2(params->fd_out, STDOUT_FILENO);
    close(params->fd_in);
    close(params->fd_out);
}
/*
void clean_pipe_fd(int ***fd,  int pipe_count)
{
    int i;

    i = 0;
    while (i < pipe_count)
    {
        close((*fd)[i][0]);
        close((*fd)[i][1]);
        free((*fd)[i]);
        i++;
    }
    free(*fd);
    *fd = NULL;
}

int put_nbr_pipes(t_cmd *command)
{
    int count;

    count = 0;
    while (command != NULL)
    {
        if (!ft_strcmp(command->cmd[0], "|"))
            count++;
        command = command->next;
    }
    return (count);
}

void init_pipe_fd(int ***fd, t_params *params)
{
    int i = 0;
    int pipe_count = put_nbr_pipes(params->command);

    *fd = (int **)malloc(sizeof(int *) * pipe_count);
    if (!*fd)
    {
        perror("malloc");
        cleanup_and_exit(params, EXIT_FAILURE);
    }

    while (i < pipe_count)
    {
        (*fd)[i] = (int *)malloc(sizeof(int) * 2);
        if (!(*fd)[i])
        {
            perror("malloc");
            clean_pipe_fd(fd, i);
            cleanup_and_exit(params, EXIT_FAILURE);
        }
        if (pipe((*fd)[i]) == -1)
        {
            perror("pipe");
            clean_pipe_fd(fd, i);
            cleanup_and_exit(params, EXIT_FAILURE);
        }
        i++;
    }
}

int setup_pipe(int **fd, t_cmd *current, int i)
{
    if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
    {
        if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
            return (perror("dup2"), -1);
    }
    if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
    {
        if (dup2(fd[i][1], STDOUT_FILENO) == -1)
            return (perror("dup2"), -1);
    }
    return (0);
}

void exec_cmd(t_params *params)
{
    int i = 0;
    int rank_cmd;
    params->fd_in = dup(STDIN_FILENO);
    params->fd_out = dup(STDOUT_FILENO);
    int nbr_pipes;
    int **fd;
    int status;
    t_cmd *current;
    pid_t pid;

    i = 0;
    status = 0;
    rank_cmd = 0;
    nbr_pipes = put_nbr_pipes(params->command);
    init_pipe_fd(&fd, params);
    current = params->command;
    if (params->envp)
        free_array(params->envp);
    params->envp = put_envp(params);
    if (!params->envp)
    {
        perror("put_envp");
        cleanup_and_exit(params, 1);
    }
    while (current != NULL)
    {
        if (!ft_strcmp(current->cmd[0], "|"))
        {
            current = current->next;
            rank_cmd++;
            continue;
        }
        if (isbuiltins(current->cmd[0]) && current->next == NULL)
        {
            if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
            {
                if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
                {
                    perror("dup2 failed");
                    cleanup_and_exit(params, EXIT_FAILURE);
                }
            }
            if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
            {
                if (dup2(fd[i][1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 failed");
                    cleanup_and_exit(params, EXIT_FAILURE);
                }
            }
            input_r(current, rank_cmd);
            output(current);
            params->last_exit_code = run_builtins(current->cmd, params);
            dup2(params->fd_in, STDIN_FILENO);
            dup2(params->fd_out, STDOUT_FILENO);
            // Fermer les pipes inutiles
            if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
                close(fd[i - 1][0]);
            if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
                close(fd[i][1]);
            current = current->next;
            continue;
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            clean_pipe_fd(&fd, nbr_pipes);
            cleanup_and_exit(params, EXIT_FAILURE);
        }
        if (pid == 0)
        {
            signal(SIGQUIT, SIG_DFL);
            if (setup_pipe(fd, current, i) == -1)
                exit(EXIT_FAILURE);
            //josia
            input_r(current, rank_cmd);
            output(current);
            clean_pipe_fd(&fd, nbr_pipes);
            if (isbuiltins(current->cmd[0]))
            {
                params->last_exit_code = run_builtins(current->cmd, params);
                free_list_cmd(params->command);
                cleanup_and_exit(params, params->last_exit_code);
            }
            if (execve(current->cmd[0], current->cmd, params->envp) == -1)
            {
                perror("execve");
                free_list_cmd(params->command);
                cleanup_and_exit(params, 127);
            }
        }
        else
        {
            if (current->previous && !ft_strcmp(current->previous->cmd[0], "|"))
                close(fd[i - 1][0]);
            if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
                close(fd[i][1]);
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                params->last_exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
            {
                if ( WTERMSIG(status) == SIGQUIT)
                {
                    printf("Quit (core dumped)\n");
                }
                else if (WTERMSIG(status) == SIGINT)
                {
                    params->last_exit_code = 128 + g_sig_num;
                }
                else
                {
                    params->last_exit_code = 128 + WTERMSIG(status);
                }
            }
        }
        if (current->next && !ft_strcmp(current->next->cmd[0], "|"))
            i++;
        rank_cmd++;
        current = current->next;
    }
    clean_pipe_fd(&fd, nbr_pipes);
}*/
