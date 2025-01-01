/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_utils_9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:21:23 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/31 13:58:26 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	h_here(t_cmd *input, int *i, int *in_rank, int here)
{
	input->rank_here = (*in_rank)++;
	input->here = here;
	free(input->cmd[*i]);
	free(input->cmd[*i + 1]);
	(*i)++;
}

static void	h_less(t_cmd *input, int *i, int *in_rank)
{
	input->rank_less = (*in_rank)++;
	if (input->less)
		free(input->less);
	input->less = ft_strdup(input->cmd[*i + 1]);
	free(input->cmd[*i + 1]);
	free(input->cmd[*i]);
	(*i)++;
}

void	del_in(t_cmd *input, int here)
{
	int	i;
	int	j;
	int	in_rank;

	i = 0;
	j = 0;
	in_rank = 0;
	while (input->cmd[i] != NULL)
	{
		if (ft_strcmp(input->cmd[i], "<<") == 0 && input->cmd[i + 1])
			h_here(input, &i, &in_rank, here);
		else if (ft_strcmp(input->cmd[i], "<") == 0 && input->cmd[i + 1])
			h_less(input, &i, &in_rank);
		else
			input->cmd[j++] = input->cmd[i];
		i++;
	}
	input->cmd[j] = NULL;
	if (j == 0)
	{
		free(input->cmd);
		input->cmd = NULL;
	}
}

void	del_out(t_cmd *out)
{
	int	i;
	int	j;
	int	out_rank;

	i = 0;
	j = 0;
	out_rank = 0;
	while (out->cmd[i] != NULL)
	{
		if ((ft_strcmp(out->cmd[i], ">") == 0 || ft_strcmp(out->cmd[i],
					">>") == 0) && out->cmd[i + 1])
			handle_out_redirection(out, &out_rank, &i, out->cmd[i]);
		else
			out->cmd[j++] = out->cmd[i];
		i++;
	}
	out->cmd[j] = NULL;
	if (j == 0)
	{
		free(out->cmd);
		out->cmd = NULL;
	}
}
