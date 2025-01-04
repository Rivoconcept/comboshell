/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_del_out_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 12:14:14 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/04 12:42:32 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_index(t_cmd *input, int index)
{
	while (input->cmd[index])
	{
		free(input->cmd[index]);
		input->cmd[index] = NULL;
		index++;
	}
	free_array(input->cmd);
	input->cmd = NULL;
}

static void	handle_error_out(t_cmd *out, char *temp, int *i)
{
	free(temp);
	free_index(out, *i);
	if (out->great)
		free(out->great);
	if (out->dgreat)
		free(out->dgreat);
	out->dgreat = NULL;
	out->great = NULL;
	out->dgreat_error = 1;
}

void	clean_handle_out_red(t_cmd *out, char *temp, int *i)
{
	out->rank_less_error--;
	free(temp);
	free(out->cmd[*i]);
	out->cmd[*i] = NULL;
	free(out->cmd[*i + 1]);
	out->cmd[*i + 1] = NULL;
	(*i)++;
}

int	handle_dgreat_red(t_cmd *out, char *temp, int *i, int *out_rank)
{
	int	returnval;
	int	file;

	returnval = 0;
	if (access(temp, F_OK) == 0 && out->rank_less_error > 0)
	{
		returnval = access(temp, W_OK);
		if (returnval != 0 && errno == EACCES)
		{
			handle_error_out(out, temp, i);
			return (1);
		}
	}
	if (out->rank_less_error > 0)
	{
		file = open(temp, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file >= 0)
			close(file);
		if (out->dgreat)
			free(out->dgreat);
		out->dgreat = ft_strdup(temp);
	}
	out->rank_dgreat = (*out_rank)++;
	return (0);
}

int	handle_great_red(t_cmd *out, char *temp, int *i, int *out_rank)
{
	int	returnval;
	int	file;

	returnval = 0;
	if (access(temp, F_OK) == 0 && out->rank_less_error > 0)
	{
		returnval = access(temp, W_OK);
		if (returnval != 0 && errno == EACCES)
		{
			handle_error_out(out, temp, i);
			return (1);
		}
	}
	if (out->rank_less_error > 0)
	{
		file = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file >= 0)
			close(file);
		if (out->great)
			free(out->great);
		out->great = ft_strdup(temp);
	}
	out->rank_great = (*out_rank)++;
	return (0);
}
