/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:57:10 by rrakoton          #+#    #+#             */
/*   Updated: 2024/11/08 15:57:10 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_redirection(s_redirection *redir)
{
    if (!redir)
        return;
    if (redir->value)
        free(redir->value);
    free(redir);
}

void handle_redirection(s_redirection **redir, e_tokentype type, char *value) {
    free_redirection(*redir);
    *redir = add_red(type, value);
}

void remove_current_element(s_element **elements, s_element **prev, s_element **current) {
    if (*prev)
        (*prev)->next = (*current)->next;
    else
        *elements = (*current)->next;
    free((*current)->value);
    free(*current);
    if(*prev)
        *current = (*prev)->next;
    else
        *current = *elements;
}