/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:35 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/24 12:38:53 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pure_apostrophe(char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"')
            j++;
        if (str[i] == '\'')
            k++;
        i++;
    }
    return (str && str[0] == '\'' && str[i - 1] == '\'' && j == 0 && k == 2);
}

int pure_quote(char *str)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'')
            j++;
        if (str[i] == '"')
            k++;
        i++;
    }
    return (str && str[0] == '"' && str[i - 1] == '"' && j == 0 && k == 2);
}

int in_single_quote(char *str)
{
    int i;
    int apostrophe;
    int quote;

    i = 0;
    apostrophe = 0;
    quote = 0;
    while (str[i] != '\0')
    {
        handle_quotes(str[i], &apostrophe, &quote);
        if (str[i] == '"' && apostrophe)
            return (1);
        i++;
    }
    return (0);
}

int in_double_quote(char *str)
{
    int i;
    int apostrophe;
    int quote;

    i = 0;
    apostrophe = 0;
    quote = 0;
    while (str[i] != '\0')
    {
        handle_quotes(str[i], &apostrophe, &quote);
        if (str[i] == '\'' && quote)
            return (1);
        i++;
    }
    return (0);
}