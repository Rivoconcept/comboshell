/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_str_without_quote.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:23:07 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/27 17:55:40 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char *format_str_without_quote(char *input)
{
    int i;
    int j;
    char *new_input;

    i = 0;
    j = 0;
    new_input = (char *)malloc(sizeof(char) * ft_strsize(input) + 1);
    if (!new_input)
        return (NULL);
    while (input[i] != '\0')
    {
        if (input[i] == '"' || input[i] == '\'')
        {
            i++;
            continue;
        }
        new_input[j] = input[i];
        i++;
        j++;
    }
    new_input[j] = '\0';
    free(input);
    return (new_input);
}
