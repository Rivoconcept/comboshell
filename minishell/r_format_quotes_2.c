/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:11:13 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 12:40:10 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
    if (c == '\'' && !(*in_double_quote))
    {
        *in_single_quote = !(*in_single_quote);
    }
    if (c == '"' && !(*in_single_quote))
    {
        *in_double_quote = !(*in_double_quote);
    }
}

int in_apostrophe(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (str && str[0] == '\'' && str[i - 1] == '\'');
}

int in_quote(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (str && str[0] == '"' && str[i - 1] == '"');
}
