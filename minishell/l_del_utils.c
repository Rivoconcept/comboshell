/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_del_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:57:15 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/24 16:50:46 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_out_redirection(t_cmd *out, int *out_rank, int *i,
		const char *type)
{
	int	file;

	if (ft_strcmp(type, ">") == 0)
	{
		file = open(out->cmd[*i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(file);
		out->rank_great = (*out_rank)++;
		if (out->great)
			free(out->great);
		out->great = ft_strdup(out->cmd[*i + 1]);
	}
	else if (ft_strcmp(type, ">>") == 0)
	{
		file = open(out->cmd[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		close(file);
		out->rank_dgreat = (*out_rank)++;
		if (out->dgreat)
			free(out->dgreat);
		out->dgreat = ft_strdup(out->cmd[*i + 1]);
	}
	free(out->cmd[*i]);
	free(out->cmd[*i + 1]);
	(*i)++;
}

void	del_here(t_cmd *input, int *in_rank, int here, int *i)
{
	input->rank_here = (*in_rank)++;
	input->here = here;
	free(input->cmd[*i]);
	free(input->cmd[*i + 1]);
	(*i)++;
}

void	del_less(t_cmd *input, int *in_rank, int *i)
{
	input->rank_less = (*in_rank)++;
	if (input->less)
		free(input->less);
	input->less = ft_strdup(input->cmd[*i + 1]);
	free(input->cmd[*i]);
	free(input->cmd[*i + 1]);
	(*i)++;
}
