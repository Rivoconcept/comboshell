/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:15:18 by rrakoton          #+#    #+#             */
/*   Updated: 2024/09/17 11:15:18 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t len)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    // Si dest et src sont les mêmes ou si len est 0, pas besoin de copier
    if (d == s || len == 0)
        return dest;

    // On copie 'len' octets de src vers dest
    while (len--)
        *d++ = *s++;

    return dest;
}

