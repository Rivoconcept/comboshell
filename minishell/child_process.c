/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:15:31 by rrakoton          #+#    #+#             */
/*   Updated: 2024/11/09 13:15:31 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void execute_child_process(char **argv, s_redirections *redirs)
{
    int fd_in;
    int fd_out;

    if (i > 0)
        dup2(pipes[i - 1][0], STDIN_FILENO);
    if (i < num_cmds - 1)
        dup2(pipes[i][1], STDOUT_FILENO);
    close_pipes(pipes, num_cmds - 1);

    if (redirs->less) {
        if(check_infile_err(redirs->less->value, "mini_shell") == 1)
        {
            fd_in = open(redirs->less->value, O_RDONLY);
            if (fd_in < 0 || dup2(fd_in, STDIN_FILENO) < 0) {
                free_redirections(redirs);
                ft_free(argv, count_array(argv));
            }
            close(fd_in);
        }
    }
    if (redirs->great) {
        fd_out = open(redirs->great->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out < 0 || dup2(fd_out, STDOUT_FILENO) < 0) {
            perror("Redirection output failed");
        }
        close(fd_out);
    }
    if (redirs->dgreat) {
        fd_out = open(redirs->dgreat->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_out < 0 || dup2(fd_out, STDOUT_FILENO) < 0) {
            perror("Append redirection failed");
        }
        close(fd_out);
    }
    free_redirections(redirs);
    ft_free(argv, count_array(argv));
    if (execvp(argv[0], argv) == -1)
    {
        perror("execvp failed");
        exit(1);
    }

    // Application des redirections
    
    execvp(argv[0], argv);
    perror(argv[0]);
    free_redirections(redirs);
    ft_free(argv, count_array(argv)); // Libération de argv seulement en cas d'échec
    exit(EXIT_FAILURE);
}
*/