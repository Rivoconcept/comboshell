/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_manage_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:45:38 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/04 12:45:38 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cleanup_here_doc(t_cmd *current, int rank_cmd)
{
	char	*rank;
	char	*file;

	rank = ft_itoa(rank_cmd);
	file = ft_strjoin(ROOT, rank);
	free(rank);
	current->here = -1;
	unlink(file);
	free(file);
}

static void	init_cmd_as_false(t_cmd *current)
{
	current->cmd = (char **)malloc(sizeof(char *) * 2);
	current->cmd[0] = (char *)malloc(sizeof(char) * 6);
	ft_strcpy(current->cmd[0], "false");
	current->cmd[1] = NULL;
}

static void	reset_cmd_to_false(t_cmd *current)
{
	free(current->cmd[0]);
	current->cmd[0] = (char *)malloc(sizeof(char) * 6);
	ft_strcpy(current->cmd[0], "false");
}

/*static void	handle_output_redirections(t_params *params)
{
	t_cmd	*current;
	t_cmd	*next;

	current = params->command;
	while (current != NULL)
	{
		next = current->next;
		del_out(current);
		if (current->dgreat_error)
			params->last_exit_code = 1;
		current = next;
	}
}*/

static void	handle_output_redirections(t_params *params)
{
	t_cmd	*current;
	t_cmd	*next;

	current = params->command;
	while (current != NULL)
	{
		next = current->next;

		// Gérer les redirections et nettoyer le tableau `cmd`
		del_out(current);

		// Gérer les erreurs spécifiques
		if (current->dgreat_error)
			params->last_exit_code = 1;

		current = next;
	}
}


void	manage_red(t_params *params)
{
	int		rank_cmd;
	t_cmd	*current;
	t_cmd	*next;

	rank_cmd = 0;
	current = params->command;
	while (current != NULL)
	{
		next = current->next;
		parse_and_check_redirections(current, params);
		del_in(current, rank_cmd);
		if (current->less_error)
		{
			if (current->here != -1)
				cleanup_here_doc(current, rank_cmd);
			if (!current->cmd)
				init_cmd_as_false(current);
			else if (current->cmd[0])
				reset_cmd_to_false(current);
			params->last_exit_code = 1;
		}
		rank_cmd++;
		current = next;
	}
	handle_output_redirections(params);
}
