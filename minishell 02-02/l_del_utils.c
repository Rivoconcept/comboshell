/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_del_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:57:15 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/04 12:41:05 by rrakoton         ###   ########.fr       */
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

int	handle_out_redirection(t_cmd *out, int *out_rank, int *i, const char *type)
{
	char	*temp;

	temp = format_quotes(out->cmd[*i + 1]);
	if (ft_strcmp(temp, "") == 0)
		ft_putstr_fd("No such file or directory\n", 2);
	if (ft_strcmp(type, ">") == 0)
	{
		if (handle_great_red(out, temp, i, out_rank))
			return (1);
	}
	else if (ft_strcmp(type, ">>") == 0)
	{
		if (handle_dgreat_red(out, temp, i, out_rank))
			return (1);
	}
	clean_handle_out_red(out, temp, i);
	return (0);
}

char	*prepare_temp_file(int num_cmd)
{
	char	*rank_cmd;
	char	*file;

	rank_cmd = ft_itoa(num_cmd);
	file = ft_strjoin(ROOT, rank_cmd);
	free(rank_cmd);
	return (file);
}
