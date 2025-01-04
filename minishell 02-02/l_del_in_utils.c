/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_del_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:07:56 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/04 12:41:49 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	h_here(t_cmd *input, int *i, int *in_rank, int here)
{
	input->rank_here = (*in_rank)++;
	input->here = here;
	free(input->cmd[*i]);
	input->cmd[*i] = NULL;
	free(input->cmd[*i + 1]);
	input->cmd[*i + 1] = NULL;
	(*i)++;
}

void	clean_h_less(t_cmd *input, int *i, int *in_rank)
{
	input->rank_less = (*in_rank)++;
	free(input->cmd[*i]);
	input->cmd[*i] = NULL;
	free(input->cmd[*i + 1]);
	input->cmd[*i + 1] = NULL;
	(*i)++;
}

int	h_less(t_cmd *input, int *i, int *in_rank)
{
	char	*file;
	int		returnval;

	file = format_quotes(input->cmd[*i + 1]);
	returnval = 0;
	if (access(file, F_OK) == 0)
	{
		returnval = access(file, R_OK);
		if (returnval != 0 && errno == ENOENT)
		{
			if (!input->less_error)
				input->less_error = 1;
		}
	}
	else
	{
		if (!input->less_error)
			input->less_error = 1;
	}
	if (input->less)
		free(input->less);
	input->less = ft_strdup(file);
	free(file);
	clean_h_less(input, i, in_rank);
	return (0);
}

void	cleanup_input_cmd(t_cmd *input, int j)
{
	input->cmd[j] = NULL;
	if (j == 0)
	{
		free(input->cmd);
		input->cmd = NULL;
	}
	if (input->less_error && input->less)
	{
		free(input->less);
		input->less = NULL;
	}
}
