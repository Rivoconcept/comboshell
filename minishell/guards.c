/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guards.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:20:39 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/17 11:46:52 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void* guard(void *ptr, char *file, int number)
{
    if (ptr == NULL) {
        fprintf(stderr, "%s:%d Out of Memory", file, number);
        exit(EXIT_FAILURE);
    }
    return ptr;
}
