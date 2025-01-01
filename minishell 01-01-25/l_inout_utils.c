/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_inout_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:43:01 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/01 13:59:04 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *filename, t_params *params, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("open failed");
		cleanup_and_exit(params, 1);
		exit(1);
	}
	return (fd);
}

void	dup2_stdout(int fd_out, char *filename)
{
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		free(filename);
		perror("dup2 failed");
		close(fd_out);
		exit(1);
	}
}

int	open_input_file(char *filename, t_params *params, int flags, int child)
{
	int	fd;

	fd = open(filename, flags);
	(void)params;
	if (fd == -1 && child == 1)
	{
		cleanup_and_exit(params, 1);
		exit(1);
	}
	if (fd == -1 && child == 0)
	{
		params->last_exit_code = 1;
	}
	return (fd);
}

int	open_input_here(char *filename, t_params *params, int flags, int child)
{
	int	fd;

	fd = open(filename, flags);
	if (fd == -1 && child == 1)
	{
		perror("open failed");
		ft_putstr_fd("warning\n", 2);
		unlink(filename);
		free(filename);
		cleanup_and_exit(params, 1);
		exit(1);
	}
	if (fd == -1 && child == 0)
		perror("open failed");
	return (fd);
}

void	dup2_stdin(int fd_in, char *filename)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		free(filename);
		perror("dup2 failed");
		close(fd_in);
		exit(1);
	}
}