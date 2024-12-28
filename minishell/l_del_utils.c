/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_del_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:57:15 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/21 11:57:15 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_out_redirection(t_cmd *out, int *out_rank, int *i, const char *type)
{
    int file;

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
