/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:28:22 by rrakoton          #+#    #+#             */
/*   Updated: 2024/09/23 04:28:22 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_next(const char *itr, int *i)
{
    if (itr[*i] != EOF && itr[*i] != '\0')
        return (1);
    return (0);
}

char peek(const char *itr, int *i)
{
    return itr[*i];
}

char next(char *itr, int *i, int length)
{
    char next;

    next = itr[*i];
    (*i) = (*i) + length;
    return next;
}
