/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:20:34 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/23 15:01:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_in(t_cmd *input, int here)
{
	int	i;
	int	j;
	int	in_rank;

	i = 0;
	j = 0;
	in_rank = 0;
	while (input->cmd[i] != NULL)
	{
		if (ft_strcmp(input->cmd[i], "<<") == 0)
		{
			del_here(input, &in_rank, here, &i);
		}
		else if (ft_strcmp(input->cmd[i], "<") == 0)
		{
			del_less(input, &in_rank, &i);
		}
		else
		{
			input->cmd[j++] = input->cmd[i];
		}
		i++;
	}
	input->cmd[j] = NULL;
}

static void	del_out(t_cmd *out)
{
	int	i;
	int	j;
	int	out_rank;

	i = 0;
	j = 0;
	out_rank = 0;
	while (out->cmd[i] != NULL)
	{
		if (ft_strcmp(out->cmd[i], ">") == 0 || ft_strcmp(out->cmd[i],
				">>") == 0)
			handle_out_redirection(out, &out_rank, &i, out->cmd[i]);
		else
			out->cmd[j++] = out->cmd[i];
		i++;
	}
	out->cmd[j] = NULL;
}

void	manage_red(t_params *params)
{
	int		rank_cmd;
	t_cmd	*current;

	rank_cmd = 0;
	current = params->command;
	while (current != NULL)
	{
		del_in(current, rank_cmd);
		rank_cmd++;
		current = current->next;
	}
	current = params->command;
	while (current != NULL)
	{
		del_out(current);
		current = current->next;
	}
}

void	input_r(t_cmd *current, int num_cmd)
{
	int		fd_in;
	char	*file;

	if (current->here >= 0 || current->less)
	{
		if (current->less && (current->here < 0
				|| current->rank_here < current->rank_less))
		{
			fd_in = open_input_file(current->less, O_RDONLY);
			dup2_stdin(fd_in, current->less);
			close(fd_in);
		}
		else if (current->here >= 0)
		{
			file = prepare_temp_file(num_cmd);
			fd_in = open_input_file(file, O_RDONLY);
			dup2_stdin(fd_in, file);
			free(file);
			close(fd_in);
		}
	}
}

void	output(t_cmd *current)
{
	int	fd_out;

	if (current->great || current->dgreat)
	{
		if (current->great && (!current->dgreat
				|| current->rank_dgreat < current->rank_great))
		{
			fd_out = open_file(current->great, O_WRONLY | O_CREAT | O_TRUNC);
			dup2_stdout(fd_out, current->great);
			close(fd_out);
		}
		else if (current->dgreat)
		{
			fd_out = open_file(current->dgreat, O_WRONLY | O_CREAT | O_APPEND);
			dup2_stdout(fd_out, current->dgreat);
			close(fd_out);
		}
	}
}
