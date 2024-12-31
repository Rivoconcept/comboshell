/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_del_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:57:15 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/31 17:56:02 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	l_init_cmd(t_cmd *cmd)
{
	cmd->here = 0;
	cmd->rank_here = 0;
	cmd->flag_less = 0;
	cmd->rank_less = 0;
	cmd->rank_great = 0;
	cmd->rank_dgreat = 0;
}

void	free_cmd_fields(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->cmd && ft_strcmp(cmd->cmd[0], "|") == 0)
	{
		free_array(cmd->cmd);
		cmd->cmd = NULL;
	}
	if (cmd->less)
	{
		free(cmd->less);
		cmd->less = NULL;
	}
	if (cmd->great)
	{
		free(cmd->great);
		cmd->great = NULL;
	}
	if (cmd->dgreat)
	{
		free(cmd->dgreat);
		cmd->dgreat = NULL;
	}
	l_init_cmd(cmd);
}

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

char	*prepare_temp_file(int num_cmd)
{
	char	*rank_cmd;
	char	*file;

	rank_cmd = ft_itoa(num_cmd);
	file = ft_strjoin("/home/rhanitra/here/josia", rank_cmd);
	free(rank_cmd);
	return (file);
}
