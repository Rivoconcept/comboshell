/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_first_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:09:05 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/08 14:14:45 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "utils.h"

int find_first_index(const char *big, const char *little)
{
    size_t i;
    size_t j;
    size_t len;

    i = 0;
    j = 0;
    len = ft_strsize((char *)little);
    if (!*little)
        return (0);
    while (big[i] != '\0' && len > 0)
    {
        j = 0;
        if (big[i] == little[j] && i != 0)
        {
            while (little[j] && j < len && big[i + j] == little[j])
                j++;
            if (little[j] == '\0')
                return (i);
        }
        i++;
    }
    return (0);
}