/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_cmd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:23:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 10:44:23 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	put_size(char **argv, int i)
{
	int	count;

	count = 0;
	while (argv[i + count])
	{
		if (argv[i + count] == NULL || ft_strcmp(argv[i + count], "|") == 0)
			break ;
		count++;
	}
	return (count);
}
int	add_separator(int var[3], char ***temp, t_cmd *cmd, char **argv)
{
	if (*temp && var[1] > 0)
	{
		(*temp)[var[1]] = NULL;
		cmd = add_command(cmd, *temp);
		*temp = NULL;
		var[2] = 0;
	}
	*temp = malloc(sizeof(char *) * 2);
	if (!*temp)
		return (free_list_cmd(cmd), perror("malloc"), 1);
	(*temp)[0] = ft_strdup(argv[var[0]]);
	if (!(*temp)[0])
		return (free_list_cmd(cmd), free(*temp), perror("strdup"), 1);
	(*temp)[1] = NULL;
	cmd = add_command(cmd, *temp);
	*temp = NULL;
	return (0);
}

int	initialize_cmd(int var[3], char ***temp, t_cmd *cmd, char **argv)
{
	if (!var[2])
	{
		var[2] = put_size(argv, var[0]);
		*temp = malloc(sizeof(char *) * (var[2] + 1));
		if (!*temp)
			return (free_list_cmd(cmd), perror("malloc"), 1);
		var[1] = 0;
	}
	if (argv[var[0]][0] != '\0')
	{
		(*temp)[var[1]] = ft_strdup(argv[var[0]]);
		if (!(*temp)[var[1]])
			return (free_list_cmd(cmd), free(temp), perror("strdup"), 1);
		var[1]++;
	}
	return (0);
}

void	check_end_cmd(int var[3], char ***temp, t_cmd **cmd, char **argv)
{
	if (!argv[var[0] + 1] || ft_strncmp(argv[var[0] + 1], "|", 1) == 0)
	{
		if (*temp && var[1] > 0)
		{
			(*temp)[var[1]] = NULL;
			(*cmd) = add_command((*cmd), *temp);
			*temp = NULL;
			var[2] = 0;
		}
	}
}*/
