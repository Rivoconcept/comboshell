/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_inout_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:43:01 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/21 09:43:01 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int open_file(char *filename, int flags)
{
    int fd = open(filename, flags, 0644);
    if (fd == -1)
{
        free(filename);
        perror("open failed");
        exit(1);
    }
    return fd;
}

void dup2_stdout(int fd_out, char *filename)
{
    if (dup2(fd_out, STDOUT_FILENO) == -1)
{
        free(filename);
        perror("dup2 failed");
        close(fd_out);
        exit(1);
    }
}

int open_input_file(char *filename, int flags)
{
    int fd = open(filename, flags);
    if (fd == -1)
{
        free(filename);
        perror("open failed");
        exit(1);
    }
    return fd;
}

void dup2_stdin(int fd_in,char *filename )
{
    if (dup2(fd_in, STDIN_FILENO) == -1)
{
        free(filename);
        perror("dup2 failed");
        close(fd_in);
        exit(1);
    }
}

char *prepare_temp_file(int num_cmd)
{
    char *rank_cmd = ft_itoa(num_cmd);
    char *file = ft_strjoin("/tmp/josia", rank_cmd);
    free(rank_cmd);
    return file;
}