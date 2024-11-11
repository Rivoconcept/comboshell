/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 08:20:34 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/29 10:00:00 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_element *redirect_io(s_element **elements, s_redirections *redirs) {
    s_element *current = *elements, *prev = NULL;
    while (current) {
        if (current->type == LESS_TOKEN || current->type == GREAT_TOKEN || 
            current->type == DGREAT_TOKEN || current->type == HERE_TOKEN)
            {
                if (current->type == LESS_TOKEN)
                    handle_redirection(&redirs->less, current->type, current->value);
                else if (current->type == GREAT_TOKEN)
                    handle_redirection(&redirs->great, current->type, current->value);
                else if (current->type == DGREAT_TOKEN)
                    handle_redirection(&redirs->dgreat, current->type, current->value);
                else if (current->type == HERE_TOKEN)
                    handle_redirection(&redirs->here, current->type, current->value);
                remove_current_element(elements, &prev, &current);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return *elements;
}

s_redirection *add_red(e_tokentype type, char *value) {
    s_redirection *redirection = malloc(sizeof(s_redirection));
    if (!redirection)
        return NULL;
    redirection->type = type;
    if(value)
        redirection->value = ft_strdup(value);
    else
        redirection->value = NULL;
    if (value && !redirection->value)
    {
        free(redirection);
        return NULL;
    }

    return redirection;
}

void free_redirections(s_redirections *redirs)
{
    free_redirection(redirs->less);
    free_redirection(redirs->great);
    free_redirection(redirs->dgreat);
    free_redirection(redirs->here);
}