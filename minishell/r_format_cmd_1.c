/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:13:30 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 17:04:08 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_access(char *command, char *path)
{
	char	*temp;

	temp = NULL;
	if (putchar_count(command, '/') > 1 && command[0] == '/')
		temp = ft_strjoin(path, (strrchr(command, '/') + 1));
	else if (!putchar_count(command, '/'))
		temp = ft_strjoin(path, command);
	if (!temp)
		return (NULL);
	if ((command[0] == '/' && (putchar_count(command, '/') == 1
				|| !find_first_index(temp, command))) || (command[0] != '/'
			&& putchar_count(command, '/')))
	{
		free(temp);
		temp = ft_strdup(command);
	}
	if (!temp)
		return (NULL);
	return (temp);
}

char	*put_path(char **dirs, char *command)
{
	int			i;
	char		*path;
	char		*full_path;
	struct stat	statbuf;

	i = 0;
	path = NULL;
	full_path = NULL;
	while (dirs[i] != NULL)
	{
		path = ft_strjoin(dirs[i], "/");
		if (!path)
			return (NULL);
		full_path = check_access(command, path);
		free(path);
		if (stat(full_path, &statbuf) == 0 && (statbuf.st_mode & S_IFREG)
			&& access(full_path, X_OK | F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*check_cmd_standard(t_params *params, char *command)
{
	char	**dirs;
	char	*path_env;
	char	*full_path;

	full_path = NULL;
	if (!command || *command == '\0')
		return (NULL);
	path_env = ft_getenv(params, "PATH");
	if (!path_env || path_env == NULL)
		return (NULL);
	dirs = ft_split(path_env, ':');
	free(path_env);
	if (!dirs)
	{
		printf("Debug: PATH directories could not be split.\n");
		return (NULL);
	}
	full_path = put_path(dirs, command);
	free_array(dirs);
	if (!full_path)
		return (NULL);
	return (full_path);
}

void	format_cmd(t_params *params)
{
	t_cmd	*current;
	char	*cmd;

	cmd = NULL;
	current = params->command;
	while (current != NULL)
	{
		if (ft_strncmp(current->cmd[0], "|", 1) == 0)
		{
			current = current->next;
			continue ;
		}
		if (!isbuiltins(current->cmd[0]))
		{
			cmd = check_cmd_standard(params, current->cmd[0]);
			if (!cmd)
				return ;
			free(current->cmd[0]);
			current->cmd[0] = cmd;
		}
		current = current->next;
	}
}
