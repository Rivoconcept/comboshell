/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:38:41 by rrakoton          #+#    #+#             */
/*   Updated: 2024/11/09 13:38:41 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_infile_err(char *infile, char *shell)
{
	if (access(infile, F_OK | R_OK) == 0)
		return (1);
	else
	{
		ft_putstr_fd("-", 2);
		ft_putstr_fd(shell, 2);
		ft_putstr_fd(": ", 2);
		perror(infile);
		return (0);
	}
}

int	check_infile(char *infile)
{
	if (access(infile, F_OK | R_OK) == 0)
		return (1);
	else
	{
		perror(infile);
		return (0);
	}
}

int	check_outfile(char *outfile, char *shell)
{
	int	fd;

	fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("-", 2);
		ft_putstr_fd(shell, 2);
		ft_putstr_fd(": ", 2);
		perror(outfile);
		return (0);
	}
	close(fd);
	return (1);
}
