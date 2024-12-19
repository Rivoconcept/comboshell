/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_redirection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:20:34 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/18 14:02:47 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_element *redirect_io(t_element **elements, t_redirections *redirs) {
    t_element *current = *elements, *prev = NULL;
    int in_rank = 0;
    int out_rank = 0;
    while (current) {
        if (current->type == LESS_TOKEN || current->type == GREAT_TOKEN || 
            current->type == DGREAT_TOKEN || current->type == HERE_TOKEN)
            {
                if (current->type == LESS_TOKEN)
                    handle_redirection(&redirs->less, current->type, current->value, in_rank++);
                else if (current->type == GREAT_TOKEN)
                    handle_redirection(&redirs->great, current->type, current->value, out_rank++);
                else if (current->type == DGREAT_TOKEN)
                    handle_redirection(&redirs->dgreat, current->type, current->value, out_rank++);
                else if (current->type == HERE_TOKEN)
                    handle_redirection(&redirs->here, current->type, current->value, in_rank++);
                remove_current_element(elements, &prev, &current);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return *elements;
}

t_redirection *add_red(e_tokentype type, char *value, int rank) {
    int file;
    t_redirection *redirection = malloc(sizeof(t_redirection));
    if (!redirection)
        return NULL;
    redirection->type = type;
    redirection->rank = rank;
    if(value)
        redirection->value = ft_strdup(value);
    else
        redirection->value = NULL;
    if (value && !redirection->value)
    {
        free(redirection);
        return NULL;
    }
    if(redirection->type == DGREAT_TOKEN)
    {
        file = open(redirection->value, O_WRONLY | O_CREAT | O_TRUNC , 0644);
        close(file);
    }
    if(redirection->type == GREAT_TOKEN)
    {
        file = open(redirection->value, O_WRONLY | O_CREAT | O_APPEND , 0644);
        close(file);
    }



    return redirection;
}

void free_redirections(t_redirections *redirs)
{
    free_redirection(redirs->less);
    free_redirection(redirs->great);
    free_redirection(redirs->dgreat);
    free_redirection(redirs->here);
}