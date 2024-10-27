/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:24:51 by rhanitra          #+#    #+#             */
/*   Updated: 2024/09/27 19:27:35 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int while_check_char(char c, char *input)
{
    int     i;

    i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == c)
            return (1);
        i++;
    }
    return (0);
}