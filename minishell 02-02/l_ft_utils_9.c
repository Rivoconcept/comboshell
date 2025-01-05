/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_ft_utils_9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:21:23 by rrakoton          #+#    #+#             */
/*   Updated: 2025/01/04 18:11:58 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (((ft_strcmp(input->cmd[i], ">") == 0 || ft_strcmp(input->cmd[i],
						">>") == 0) && input->cmd[i + 1]) && !input->less_error)
			input->rank_less_error++;
		if (ft_strcmp(input->cmd[i], "<<") == 0 && input->cmd[i + 1])
			h_here(input, &i, &in_rank, here);
		else if (ft_strcmp(input->cmd[i], "<") == 0 && input->cmd[i + 1])
			h_less(input, &i, &in_rank);
		else
			input->cmd[j++] = input->cmd[i];
		i++;
	}
	cleanup_input_cmd(input, j);
}

static void	set_false_out(t_cmd *out)
{
	out->cmd = (char **)malloc(sizeof(char *) * 2);
	out->cmd[0] = (char *)malloc(sizeof(char) * 6);
	ft_strcpy(out->cmd[0], "false");
	out->cmd[1] = NULL;
}

static void	cleanup_output_cmd(t_cmd *out, int j)
{
	out->cmd[j] = NULL;
	if (j == 0)
	{
		free(out->cmd);
		out->cmd = NULL;
	}
}

char	**delete_null_in_out(t_cmd **out, int size)
{
	int		i;
	int		j;
	char	**new_cmd;

	new_cmd = malloc((size + 1) * sizeof(char *));
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	new_cmd = malloc((size + 1) * sizeof(char *));
	if (!new_cmd)
		return (NULL);
	while ((*out)->cmd[i])
	{
		while ((*out)->cmd[i] == NULL)
		{
			i++;
			if (i > size)
				break;
		}
		if ((*out)->cmd[i])
		new_cmd[j] = (*out)->cmd[i];
		i++;
		j++;
	}
	new_cmd[j] = NULL;
	return (new_cmd);
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
		{
			if (handle_out_redirection(out, &out_rank, &i, out->cmd[i]))
			{
				set_false_out(out);
				return ;
			}
		}
		else
			out->cmd[j++] = out->cmd[i];
		i++;
	}
	cleanup_output_cmd(out, j);
}


