/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:02:23 by rhanitra          #+#    #+#             */
/*   Updated: 2024/10/12 19:03:19 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int echap_quote(char c, int *in_single_quote, int *in_double_quote)
{
    if (c == '\'' && !(*in_double_quote) && !(*in_single_quote))
    {
        *in_single_quote = !(*in_single_quote);
        return (1);
    }
    if (c == '\'' && !(*in_double_quote) && *in_single_quote) 
    {
        *in_single_quote = !(*in_single_quote);
        return (1);
    }
    if (c == '"' && !(*in_single_quote) && !(*in_double_quote))
    {
        *in_double_quote = !(*in_double_quote);
        return (1);
    }
    if (c == '"' && !(*in_single_quote) && *in_double_quote) 
    {
        *in_double_quote = !(*in_double_quote);
        return (1);
    }
    return (0);
}

char *format_quotes(char *command)
{
    int i = 0;
    int j = 0;
    int in_single_quote = 0;
    int in_double_quote = 0;
    char *new_path;

    new_path = (char *)malloc(sizeof(char) * ft_strsize(command) + 1);
    if (!new_path)
        return (NULL);
    while (command[i] != '\0')
    {
        if (echap_quote(command[i], &in_single_quote, &in_double_quote))
        {
            i++;
            continue;
        }
        new_path[j] = command[i];
        i++;
        j++;
    }
    new_path[j] = '\0';
    return (new_path);
}