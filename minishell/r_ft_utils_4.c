/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/29 17:58:53 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_msg(char *path, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(error, 2);
}

int	check_errors_path(char *path, char *parent_path, struct stat *statbuf,
		char *last_slash)
{
	if (path[0] != '/' && access(path, X_OK) != 0)
	{
		perror_msg((char *)path, ": command not found\n");
		return (127);
	}
	if (last_slash && last_slash != parent_path)
	{
		*last_slash = '\0';
		if (stat(parent_path, statbuf) != 0)
		{
			perror(path);
			return (127);
		}
		if (!S_ISDIR(statbuf->st_mode))
		{
			perror_msg((char *)path, ": Not a directory\n");
			return (126);
		}
	}
	return (0);
}
int	check_path(const char *path, t_params *params)
{
	struct stat	statbuf;
	char		*last_slash;
	char		parent_path[1024];

	if (!path || path[0] == '\0')
		return (0);
	ft_strlcpy(parent_path, path, sizeof(parent_path) - 1);
	parent_path[sizeof(parent_path) - 1] = '\0';
	last_slash = ft_strrchr(parent_path, '/');
	params->last_exit_code = check_errors_path((char *)path, parent_path,
			&statbuf, last_slash);
	if (params->last_exit_code != 0)
		return (params->last_exit_code);
	if (stat(path, &statbuf) != 0)
	{
		perror_msg((char *)path, ": No such file or directory\n");
		return (127);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		perror_msg((char *)path, ": is a directory\n");
		return (126);
	}
	return (0);
}
