/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:13:30 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 19:44:43 by rhanitra         ###   ########.fr       */
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
		perror_msg(": Debug: PATH directories could not be split.\n", NULL);
		return (NULL);
	}
	full_path = put_path(dirs, command);
	free_array(dirs);
	if (!full_path)
		return (ft_strdup(command));
	return (full_path);
}

void reformat_cmd(t_cmd **current)
{
    char    **argv;
    if (find_char((*current)->cmd[0], ' '))
    {
        argv = ft_split((*current)->cmd[0], ' ');
        if (!argv || !argv[0])
        {
            free_array(argv); 
            return;
        }
        free_array((*current)->cmd);
        (*current)->cmd = NULL;
        (*current)->cmd = argv;
    }
}

int	check_error_command(t_params *params, t_cmd **current, char *cmd)
{
	if (cmd == NULL)
	{
		if (check_cmd_not_found(params, (*current)->cmd[0]))
			return (1);
	}
	else
	{
		free((*current)->cmd[0]);
		(*current)->cmd[0] = cmd;
	}
	return (0);
}

int format_cmd(t_params *params)
{
    t_cmd   *current;
    char    *cmd;

    current = params->command;
    while (current != NULL)
    {
        if (current->cmd[0] && ft_strncmp(current->cmd[0], "|", 1) == 0)
        {
            current = current->next;
            continue;
        }
        if (current->cmd[0] && !isbuiltins(current->cmd[0]))
        {
            if (find_char(current->cmd[0], ' '))
                reformat_cmd(&current);
            cmd = check_cmd_standard(params, current->cmd[0]);
			if (check_error_command(params, &current, cmd))
				return (1);
        }
        current = current->next;
    }
    return (0);
}

