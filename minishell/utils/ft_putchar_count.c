/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:09:43 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 17:26:21 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int putchar_count(const char *src, char c)
{
    size_t i;
    size_t count;

    i = 0;
    count = 0;
    if (!*src)
        return (0);
    while (src[i] != '\0')
    {
        if (src[i] == c)
            count++;
        i++;
    }
    return (count);
}