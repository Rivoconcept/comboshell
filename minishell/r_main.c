/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:46:29 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/25 15:59:43 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

// https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?pli=1&gid=0#gid=0

// https://www.youtube.com/watch?v=ubt-UjcQUYg;
// https://www.youtube.com/watch?v=SToUyjAsaFk

void print_argv(char **argv)
{
    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }

}

void print_cmd(t_params *params)
{
    t_cmd *current = params->cmd;

    while (current != NULL)
    {
        print_argv(current->cmd);
        current = current->next;
    }
}

int execution(t_params *params, char *input)
{
    int fd[2] = {-1, -1}; // Initialiser à -1 pour détecter les erreurs
    int in_fd = -1;       // Utilisé pour le pipe précédent
    pid_t pid;
    t_cmd *current = params->cmd;

    /*if (current->next == NULL)
    {
        if (run_builtins(params->cmd->cmd, params, input))
        {
            free(input);
            free_list_cmd(params->cmd);
            return (0) ;
        }
    }*/
    if (!current->cmd || !current->cmd[0])
        return (0);
    while (current != NULL)
    {
        // Crée un nouveau pipe sauf pour la dernière commande
        if (current->next != NULL && pipe(fd) == -1)
        {
            perror("Pipe error");
            return (1);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("Fork error");
            close_pipe(fd);
            return (1);
        }
        else if (pid == 0) // Processus enfant
        {
           if (in_fd != -1)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (current->next != NULL)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            if (isbuiltins(current->cmd[0]))
            {
                run_builtins(current->cmd, params, input);
                exit(0);
            }
            int error = execve(current->cmd[0], current->cmd, params->envp);
            if (error == -1)
            {
                cleanup_and_exit(params, input, 127);
            }
        }
        else // Processus parent
        {
            if (in_fd != -1)
                close(in_fd);
            if (current->next != NULL)
                close(fd[1]);

            in_fd = fd[0];
            current = current->next;
        }
    }

    waitpid(pid, &params->status, 0);
    put_val_exit_status(params);
    if (WIFEXITED(params->status) && WEXITSTATUS(params->status) != 0)
    {
        fprintf(stderr, "Error: Command exited with status %d\n", WEXITSTATUS(params->status));
    }
    if (in_fd != -1)
        close(in_fd);

    return (0);
}

int run_single_cmd(t_params *params, char *input)
{
    if (count_cmd(params) == 1)
    {
        if (run_builtins(params->cmd->cmd, params, input))
        {
            free(input);
            free_list_cmd(params->cmd);
            return (1);
        }
    }
    return (0);
}

void run_minishell(char *input, t_params *params)
{
    while (1)
    {
        input = readline("minishell$> ");
        if (*input)
            add_history(input);
        if (check_behavior(input))
        {
            free(input);
            continue ;
        }
        params->cmd = return_commands(input, params);
        if (!params->cmd)
        {
            free(input);
            continue ;
        }      
        if (run_single_cmd(params, input))
            continue ;
        if (cmd_not_found(params, input))
            continue;
        execution(params, input);
        //exec(params->cmd);
        free(input);
        free_list_cmd(params->cmd);
        input = NULL;
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *input;
    signal_handlers(SIGCHLD);
    signal_handlers(SIGINT);
    signal_handlers(SIGQUIT);

    input = NULL;
    t_params *params = create_list_params(envp);
    if (!params)
        return (1);
    run_minishell(input, params);
    cleanup_and_exit(params, input, 1);
    return (0);
}

