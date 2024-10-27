/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 09:53:40 by rrakoton          #+#    #+#             */
/*   Updated: 2024/09/23 09:53:40 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_word(char *str, int *start)
{
    int i;
    int dquote;
    int squote;

    i = *start;
    dquote = 0;
    squote = 0;
    while (str[i]) {
        if (squote == 0 && str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
            dquote = !dquote;
        else if (dquote == 0 && str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
            squote = !squote;
        if (!squote && !dquote && (str[i] == '|' || str[i] == ';'))
            break;
        i++;
    }
    return (i - *start);
}

s_token scanner_peek(char *itr, int *i)
{
    char c;
    e_tokentype type;
    char *start = &itr[*i];
    int length = 1;

    c = peek(itr, i);
    if (c == EOF || c == '\0')
        type = END_TOKEN;
    else if (c == '|')
        type = PIPE_TOKEN;
    else if (c == ';')
        type = COL_TOKEN;
    else
    {
        type = CMD_TOKEN;
        length = len_word(itr, i);
    }
    s_slice location = {
        start,
        length
    };
    s_token token = {
        type,
        location
    };
    return token;
}

int scanner_has_next(char *itr, int *i)
{
    char c = itr[*i];
    switch (c) {
        case EOF:
        case '\0':
            return 0;
        default:
            return 1;
    }
}

s_token scanner_next(char *itr, int *i)
{
    s_token t_next = scanner_peek(itr, i);

    if (scanner_has_next(itr, i)) {
        next(itr, i, t_next.location.length);
        return t_next;
    } else {
        return t_next;
    }
}