/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:40:30 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/10 11:40:30 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_shell(char *path)
{
	char	*shell;
	int		i;
	int		j;

	i = ft_strlen(path) - 1;
	j = 0;
	while (path[i] != '/')
		i--;
	shell = (char *)malloc(sizeof(char) * ((ft_strlen(path) - i)));
	while (path[++i] != '\0')
		shell[j++] = path[i];
	shell[j] = '\0';
	free(path);
	return (shell);
}

static int	nbr_cmd(char *path, char *cmd)
{
	char	**split_path;
	int		i;
    int nbr;

	i = 0;
    nbr = 0;
	split_path = ft_split(path, ':');
	
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		split_path[i] = ft_strjoin(split_path[i], cmd);
		if (access(split_path[i], F_OK | X_OK) == 0)
            nbr++;
        else
            free(split_path[i]);
		i++;
	}
   	free(split_path);
	return (nbr);
}

static char	**check_cmd(char *path, char *cmd)
{
	char	**split_path;
	char	**list_path;
	int		i;
	int j;

	i = 0;
	j = 0;
	split_path = ft_split(path, ':');
	list_path =  (char **)malloc((nbr_cmd(path, cmd) + 1) * sizeof(char *));
	free(path);
	while (split_path[i])
	{
		split_path[i] = ft_strjoin(split_path[i], "/");
		split_path[i] = ft_strjoin(split_path[i], cmd);
		if (access(split_path[i], F_OK | X_OK) == 0)
           list_path[j++] = ft_strdup(split_path[i]);
		i++;
	}
	list_path[j] = NULL;
   	ft_free(split_path, i);
	return (list_path);
}

char *is_valid_cmd(char *path, char *cmd)
{
	char **path_array;
	char *is_path;

	if(is_executable_name(cmd))
	{
		path_array = check_cmd(path, cmd);
		is_path = ft_strdup(path_array[0]);
		ft_free(path_array, ft_sublen(path_array));
	}
	else
	{
		is_path = simplify_path(cmd);
		if (access(is_path, F_OK | X_OK) != 0)
           is_path = NULL;
	}
	return (is_path);
}

 /*printf("path: %s", is_valid_cmd(get_path(&(*envp), "PATH"), "/usr/bin/ls"));

             Simplifier le chemin
            char *simplified = simplify_path(input);
            printf("Chemin simplifié : %s\n", simplified);

            free(simplified);*/
