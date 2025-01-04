/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_monitor_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:39:51 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/04 12:39:51 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file_for_writing(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	display_error(char *tmp)
{
	if (access(tmp, F_OK) != 0)
	{
		perror(tmp);
		free(tmp);
		return (-1);
	}
	else if (access(tmp, R_OK) != 0)
	{
		perror(tmp);
		free(tmp);
		return (-1);
	}
	return (0);
}

int	handle_redirection(char *file, int mode)
{
	char	*tmp;

	tmp = format_quotes(file);
	if (mode == O_RDONLY)
	{
		if (display_error(tmp))
			return (-1);
	}
	else if (mode == O_WRONLY)
	{
		if (open_file_for_writing(tmp) < 0)
		{
			free(tmp);
			return (-1);
		}
	}
	free(tmp);
	return (0);
}

void	parse_and_check_redirections(t_cmd *current)
{
	int	i;

	i = 0;
	while (current->cmd[i])
	{
		if (ft_strcmp(current->cmd[i], "<") == 0 && current->cmd[i + 1])
		{
			if (handle_redirection(current->cmd[++i], O_RDONLY) < 0)
				return ;
		}
		else if ((ft_strcmp(current->cmd[i], ">") == 0
				|| ft_strcmp(current->cmd[i], ">>") == 0) && current->cmd[i
				+ 1])
		{
			if (handle_redirection(current->cmd[++i], O_WRONLY) < 0)
				return ;
		}
		i++;
	}
}
