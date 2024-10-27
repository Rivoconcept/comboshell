/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:13:30 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 15:49:18 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rivo.h"

char *check_access(char *full_path, char *command, char *path)
{
    if (putchar_count(command, '/') > 1 && command[0] == '/')
        full_path = ft_strjoin(path, (ft_strrchr(command, '/') + 1));
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
	char	**dirs;
    char    *path_env;
	char    *full_path;

	full_path = NULL;
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	full_path = put_path(dirs, command);
	free_array(dirs);
	if (!full_path)
    {
        printf("%s : command not found\n", command);
		return (ft_strdup(""));
    }
	return (full_path);
}

char	**format_argv(char *input)
{
	int     i;
    char    **argv;
    char	*new_input;
    char    *temp;

	i = 0;
    new_input = format_input(input, "&|<>;");
	argv = parse_command(new_input);
    while (argv[i] != NULL)
    {
        if (i == 0  || token_type(argv[i]) == 1 || token_type(argv[i]) == 3
            || (token_type(argv[i]) == 2) || token_type(argv[i - 1]) == 1)
        {
            temp = format_quotes(argv[i]);
            free(argv[i]);
            argv[i] = temp;
        }
        i++;
    }
    free(new_input);
	return (argv);
}



char	**put_argv(char **argv, char *input, t_params *params)
{
	char	*cmd;

	cmd = NULL;
	argv = format_argv(input);
    format_variable(argv, params);
    del_quotes(argv);

    int i = 0;
    while (argv[i] != NULL)
    {
        printf("%s\n", argv[i]);
        i++;
    }
	if (!isbuiltins(argv[0]))
		cmd = check_cmd_standard(argv[0]);
	else
		cmd = check_cmd_builtins(argv[0]);
	if (cmd != NULL)
	{
		free(argv[0]);
		argv[0] = ft_strdup(cmd);
        free(cmd);
		return (argv);
	}
	else
	{
		printf("%s : command not found\n", argv[0]);
		free_array(argv);
	}
	return (free(cmd), NULL);
}