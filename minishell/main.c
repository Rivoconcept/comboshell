/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:46:29 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/19 21:22:50 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?pli=1&gid=0#gid=0

// https://www.youtube.com/watch?v=ubt-UjcQUYg;
// https://www.youtube.com/watch?v=SToUyjAsaFk

void put_val_exit_status(t_wstatus *status, int wstatus)
{
    int sig;

    sig = 0;
    if (WIFSIGNALED(wstatus))
    {
        sig = WTERMSIG(wstatus);
        if (sig == SIGINT)
            status->value = 128 + sig;
    }
    else if (WIFEXITED(wstatus))
        status->value = WEXITSTATUS(wstatus);
}

int execution(char **argv, char **envp, t_wstatus *status)
{
    pid_t   pid;
    int     val;
    int     wstatus;

    wstatus = 0;
    pid = fork();
    if (pid == -1)
    {
        perror("Unsuccessuf");
        return (-1);
    }
    if (pid == 0)
    {
            val = execve(argv[0], argv, envp);
            if (val == -1)
                return (1);
    }
    else
    {
        waitpid(pid, &wstatus, 0);
        put_val_exit_status(status, wstatus);
    }
    return (0);
}

int main(int argc, char **argv, char **envp)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    // Set up SIGINT handler (ctrl-C)
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART; // Restart functions if interrupted by handler
    sigaction(SIGINT, &sa_int, NULL);

    // Set up SIGQUIT handler (ctrl-\)
    sa_quit.sa_handler = handle_sigignor;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
    char *input;
    // char *cd[2];
    char    *prompt;
    t_wstatus status = {0};
    
    (void)argc;
    input = NULL;
    // cd[0] = "./builtins/bin/cd";
    // cd[1] =NULL;
    prompt = NULL;
    while (1)
    {
        // if (!ft_strcmp(argv[0], "./builtins/bin/cd"))
        //     ;
        // else
        //     print_prompt();
        prompt = "minishell$>";
        input = readline(prompt);
        handle_sigquit(input);
        // free(prompt);
        if (input && *input)
            add_history(input);
        if (check_behavior(input))
        {
            free(input);
            continue;
        }
        argv = put_argv(argv, input);
        if (argv == NULL)
        {
            free(input);
            continue;
        }
        /*int i = 0;
        while (argv[i] != NULL)
        {
            printf("%s\n", argv[i]);
            i++;
        }*/
        execution(argv, envp, &status);
        if (!ft_strcmp(argv[0], "./builtins/exec/exit"))
        {
            free(input);    
            free_array(argv);
            rl_clear_history();
            break;
        }
        free(input);
        free_array(argv);
    }
    rl_clear_history();
    return (0);
}