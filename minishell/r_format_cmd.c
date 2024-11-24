/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:13:30 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/23 13:08:20 by rhanitra         ###   ########.fr       */
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

char *check_cmd_standard(t_params *params, char *command)
{
    char **dirs;
    char *path_env;
    char *full_path;

    full_path = NULL;
    path_env = ft_getenv(params, "PATH");
    if (!path_env)
    {
        printf("minishell: %s: command not found\n", command);
        return (ft_strdup(""));
    }
    dirs = ft_split(path_env, ':');
    if (!dirs)
    {
        printf("Debug: PATH directories could not be split.\n");
        return (ft_strdup(""));
    }
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
    char    *temp;

	i = 0;
	argv = parse_command(input);
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
	return (argv);
}

char	**put_argv(char *input, t_params *params)
{
	char	*cmd;
    char    **command;

	cmd = NULL;
	command = format_argv(input); 
    format_variable(command, params);
    del_quotes(command);
    if (put_var_temp(command, params))
    {
        free_array(command);
        return (NULL);
    }
	else if (!isbuiltins(command[0]))
		cmd = check_cmd_standard(params, command[0]);
	else
		cmd = ft_strdup(command[0]);
	if (cmd != NULL)
	{
		free(command[0]);
		command[0] = cmd;
		return (command);
	}
    printf("%s : command not found\n", command[0]);
    free_array(command);
	return (NULL);
}
