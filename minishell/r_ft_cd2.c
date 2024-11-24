/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:11:07 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/20 16:18:53 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

char	*split_path(char **dirs, char *temp_path, t_params *params)
{
	int	i;
	char *temp;

	i = 0;
	temp = NULL;
	while (dirs[i] != NULL)
	{
		if (standard_path(dirs, &i, &temp_path, params))
			continue ;
		temp = join_paths(temp_path, dirs[i]);
		free(temp_path);
		temp_path = temp;
		i++;
	}
	return (free_array(dirs), temp_path);
}

char	*format_tilde(t_params *params, char **dirs)
{
	int		i;
	char	*home;
	char	*temp;
	char	*new_path;

	i = 1;
	temp = NULL;
	home = ft_getenv(params, "HOME");
	if (!home)
		return (printf("minishell: cd: HOME not set\n"), NULL);
	new_path = ft_strdup(home);
	while (dirs[i] != NULL)
	{
        temp = ft_strjoin(new_path, "/");
        free(new_path);
        new_path = temp;
        temp = ft_strjoin(new_path, dirs[i]);
        free(new_path);
        new_path = temp;
        i++;
	}
    return (free_array(dirs), new_path);
}

char	*return_new_path(const char *arg, t_params *params)
{
	char	*cwd;
	char	**dirs;
	char	*new_path;
	char	*temp_path;

	new_path = NULL;
	temp_path = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("Error on getcwd"), ft_strdup(""));
	if (arg == NULL || (!ft_strcmp(arg, "~") && ft_strlen(arg) == 1)) 
		return (free(cwd), ft_strdup(get_home(params)));
	if (!ft_strcmp(arg, "/") && ft_strlen(arg) == 1)
		return (free(cwd), ft_strdup("/"));
	dirs = ft_split(arg, '/');
	if (arg[0] == '~')
		return (free(cwd), format_tilde(params, dirs));
	temp_path = ft_strdup(cwd);
	if (dirs == NULL)
		return (free(cwd), temp_path);
	new_path = split_path(dirs, temp_path, params);
	return (free(cwd), new_path);
}

int	ft_cd(const char *arg, t_params *params)
{
	int		i;
	char	*new_path;

	i = 0;
    while (params->cmd->cmd[i] != NULL)
        i++;
    if (i > 2)
        return (printf("minishell: cd: too many arguments\n"), 1);
    new_path = return_new_path(arg, params);
	if (new_path && access(new_path, F_OK) == 0)
	{
		if (chdir(new_path) != 0)
			return (perror("Error on cd"), free(new_path), 1);
		free(new_path);
	}
	else
		return (printf("minishell: cd: %s: is not a directory\n", new_path),
		free(new_path), 1);
	return (0);
}
