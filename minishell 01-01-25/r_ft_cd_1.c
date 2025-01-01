/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_cd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:11:07 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/01 13:25:26 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*format_tilde(t_params *params, char **dirs, char *cwd)
{
	int		i;
	char	*home;
	char	*temp;
	char	*new_path;

	i = 0;
	temp = NULL;
	free(cwd);
	home = ft_getenv(params, "HOME");
	if (!home)
		return (perror_msg(": cd: HOME not set\n", NULL), NULL);
	new_path = ft_strdup(home);
	while (dirs[++i] != NULL)
	{
		temp = ft_strjoin(new_path, "/");
		free(new_path);
		new_path = temp;
		temp = ft_strjoin(new_path, dirs[i]);
		free(new_path);
		new_path = temp;
	}
	free(home);
	free_array(dirs);
	return (new_path);
}

char	*return_new_path(const char *arg, t_params *params)
{
	char	*cwd;
	char	**dirs;
	char	*new_path;

	new_path = NULL;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("Error on getcwd");
		return (ft_strdup(""));
	}
	dirs = ft_split(arg, '/');
	if (arg[0] == '~')
		return (format_tilde(params, dirs, cwd));
	free(cwd);
	return (new_path);
}

void	handle_cd(int *i, char *arg, char *new_path, t_params *params)
{
	char	*temp;

	temp = NULL;
	if (*i == 1)
	{
		temp = ft_getenv(params, "HOME");
		ft_strlcpy(new_path, temp, 256);
		free(temp);
	}
	else if (arg)
	{
		temp = ft_strdup(arg);
		ft_strlcpy(new_path, temp, 256);
		free(temp);
	}
	if (arg && arg[0] == '~')
	{
		temp = return_new_path(arg, params);
		ft_strlcpy(new_path, temp, 256);
		free(temp);
	}
	if (arg && !ft_strncmp(arg, "/", ft_strlen(arg)))
		ft_strlcpy(new_path, "/", 256);
}
