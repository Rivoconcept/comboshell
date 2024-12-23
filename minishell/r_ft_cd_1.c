/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_cd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 15:11:07 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 16:00:02 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home(t_params *params)
{
	char	*home;

	home = ft_getenv(params, "HOME");
	if (!home || home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		return (NULL);
	}
    return (home);
}

char	*return_pdir(const char *cwd)
{
	size_t	len;
	char	*path;
	char	*last_slash;

	last_slash = ft_strrchr(cwd, '/');
	if (!last_slash || last_slash == cwd)
		return (ft_strdup("/"));
	len = last_slash - cwd;
	path = malloc(sizeof(char) * (len + 1));
	if (path)
	{
		ft_strlcpy(path, cwd, len + 1);
		path[len] = '\0';
	}
	return (path);
}

char	*join_paths(const char *path1, const char *path2)
{
	int		len1;
	int		len2;
	char	*new_path;

	len1 = ft_strlen(path1);
	len2 = ft_strlen(path2);
	new_path = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!new_path)
		return (NULL);
	ft_strlcpy(new_path, (char *)path1, len1 + 1);
	if (path1[len1 - 1] != '/')
		ft_strlcat(new_path, "/", len1 + len2 + 2);
	ft_strlcat(new_path, path2, len1 + len2 + 2);
	return (new_path);
}

int	standard_path(char **dirs, int *i, char **temp_path, t_params *params)
{
	char *temp;

	temp = NULL;
	if (!ft_strcmp(dirs[*i], "~"))
	{
		(*i)++;
		temp = join_paths(*temp_path, get_home(params));
		free(*temp_path);
		*temp_path = temp;
		return (1);
	}
	if (ft_strcmp(dirs[*i], ".") == 0 && ft_strlen(dirs[*i]) == 1)
		return ((*i)++, 1);
	if (ft_strcmp(dirs[*i], "..") == 0 && ft_strlen(dirs[*i]) == 2)
	{
		(*i)++;
		temp = return_pdir(*temp_path);
		free(*temp_path);
		*temp_path = temp;
		return (1);
	}
	return (0);
}
