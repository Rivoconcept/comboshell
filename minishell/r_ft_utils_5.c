/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:42:38 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 11:34:32 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_input_is_all_space(char *input)
{
	int	i;

	if (!input || !strcmp(input, "\0"))
		return (0);

	i = 0;
	while (input[i])
	{
		if (!ft_is_space(input[i]) && input[i] != '\'' && input[i] != '"')
			return (0);
		i++;
	}
	return (1);
}

char	*check_is_path(char *command, char *path)
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

char	*check_access_path(char **dirs, char *command)
{
	int		i;
	char	*path;
	char	*full_path;
	struct	stat statbuf;
	
	i = 0;
	path = NULL;
	full_path = NULL;
	while (dirs[i] != NULL)
	{
		path = ft_strjoin(dirs[i], "/");
		if (!path)
			return (NULL);
		full_path = check_is_path(command, path);
		free(path);
		if (stat(full_path, &statbuf) == 0 && (statbuf.st_mode & S_IFREG) 
			&& access(full_path, X_OK | F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	is_command(t_params *params, char *command)
{
	char	**dirs;
	char	*path_env;
	char	*full_path;

	full_path = NULL;
	if (!command || *command == '\0')
		return (0);
    if (isbuiltins(command))
    {
        return (1);
    }
	path_env = ft_getenv(params, "PATH");
	if (!path_env || path_env == NULL)
		return (0);
	dirs = ft_split(path_env, ':');
	free(path_env);
	if (!dirs)
	{
		printf("Debug: PATH directories could not be split.\n");
		return (0);
	}
	full_path = put_path(dirs, command);
	free_array(dirs);
	if (!full_path)
		return (0);
    free(full_path);
	return (1);
}