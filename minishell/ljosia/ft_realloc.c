/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:13:51 by rrakoton          #+#    #+#             */
/*   Updated: 2024/10/27 15:08:36 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ljosia.h"

void *ft_realloc(void *ptr, size_t new_size)
{
    void *new_ptr;

    if (ptr == NULL)
        return malloc(new_size);
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
        return NULL;
    ft_memcpy(new_ptr, ptr, new_size);
    free(ptr);
    return new_ptr;
}
