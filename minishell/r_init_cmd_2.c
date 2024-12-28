/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:23:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/27 14:24:36 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmd(t_cmd **cmd, char ***temp)
{
	reset_cmd_flags(*cmd);
	if (*temp)
		free(*temp);
}

t_cmd	*init_command(char **argv)
{
	t_cmd	*cmd;
	char	**temp;
	int		var[3];

	cmd = NULL;
	temp = NULL;
	var[0] = 0;
	var[1] = 0;
	var[2] = 0;
	while (argv[var[0]] != NULL)
	{
		if (ft_strcmp(argv[var[0]], "|") == 0)
		{
			if (add_separator(var, &temp, cmd, argv))
				return (NULL);
		}
		else
		{
			if (initialize_cmd(var, &temp, cmd, argv))
				return (NULL);
			check_end_cmd(var, &temp, &cmd, argv);
		}
		var[0]++;
	}
	return (clean_cmd(&cmd, &temp), cmd);
}