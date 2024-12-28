/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_cmd_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:13:30 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 11:53:00 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_access(char *full_path, char *command, char *path)
{
    if (putchar_count(command, '/') > 1 && command[0] == '/')
        full_path = ft_strjoin(path, (strrchr(command, '/') + 1));
    else if (!putchar_count(command, '/'))
        full_path = ft_strjoin(path, command);
    free(path);
    if (!full_path)
        return (NULL);
    if ((command[0] == '/' && (putchar_count(command, '/') == 1 
    || !find_first_index(full_path, command)))
    || (command[0] != '/' && putchar_count(command, '/')))
    {
        free(full_path);
        full_path = strdup(command);
    }
    if (!full_path)
        return (NULL);
    return (full_path);
}

char *put_path(char **dirs, char *command)
{
	int		i;
	char	*path;
    char    *full_path;

    i = 0;
	path = NULL;
    full_path = NULL;
	while (dirs[i] != NULL)
	{
        path = ft_strjoin(dirs[i], "/");
    	if (!path)
			return (NULL);
        full_path = check_access(full_path, command, path);
    	if (!full_path)
			return (NULL);
        if (access(full_path, X_OK | F_OK) == 0)
			return (full_path);
		free(full_path);
        i++;
	}
    return (NULL);
}

char *check_cmd_standard(char *command)
{
    char **dirs;
    char *path_env;
    char *full_path;

    full_path = NULL;
    path_env = getenv("PATH");
    if (!path_env)
        return (printf("Debug: PATH environment variable is not found.\n"), NULL);
    dirs = ft_split(path_env, ':');
    if (!dirs)
    {
        printf("Debug: PATH directories could not be split.\n");
        return (NULL);
    }
    full_path = put_path(dirs, command);
    free_array(dirs);
    if (!full_path || full_path == NULL)
	{
        return (ft_strdup(command));
	}
    return (full_path);
}
void	format_cmd(t_params *params)
{
	t_cmd	*current;
	char	*cmd;

	current = params->command;
	while (current != NULL)
	{
		if (current->cmd[0] && ft_strcmp(current->cmd[0], "|") == 0)
		{
			current = current->next;
			continue;
		}
		if (!isbuiltins(current->cmd[0]))
		{
			cmd = check_cmd_standard(current->cmd[0]);
			if (!cmd)
				return;
			free(current->cmd[0]);
			current->cmd[0] = cmd;
		}

		current = current->next;
	}
}
