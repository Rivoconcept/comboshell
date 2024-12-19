/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_here_doc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:40:36 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/18 09:10:02 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_heredoc_char(int ascii_value) {
    if ((ascii_value >= 33 && ascii_value <= 34) ||
        (ascii_value == 35) ||
        (ascii_value >= 37 && ascii_value <= 38) ||
        (ascii_value >= 40 && ascii_value <= 43) ||
        (ascii_value >= 45 && ascii_value <= 46) ||
        (ascii_value >= 48 && ascii_value <= 57) ||
        (ascii_value >= 58 && ascii_value <= 59) ||
        (ascii_value >= 63 && ascii_value <= 64) ||
        (ascii_value >= 65 && ascii_value <= 90) ||
        (ascii_value >= 94 && ascii_value <= 95) ||
        (ascii_value >= 97 && ascii_value <= 122) ||
        (ascii_value == 126)) {
        return 1;
    }
    return 0;
}

static int count_heredoc(char *input)
{
    int i;
    int nbr;

    i = 0;
    nbr = 0;
    while(input[i])
    {
        if (input[i-1] != '\\' && (input[i] == '"' || input[i] == '\''))
            i = dquote_length(input, i, input[i]);
        if(input[i-1] != '\\' && input[i] == '<' && input[i+1] == '<')
        {
            nbr++;
            i++;
        }
        i++;
    }
    return (nbr);
}

static int key_len (char *str, int pos)
{
    while(str[pos])
    {
        if (!(is_valid_heredoc_char(str[pos])))
           return (pos++);
        pos++;
    }
    return (pos);
}

char **here_key(char *input)
{
    int i;
    int j;
    char **keys;

    i = 0;
    j = 0;
    keys = (char **)malloc(sizeof(char *) * (count_heredoc(input) + 1));
    while(input[i])
    {
        if (input[i-1] != '\\' && (input[i] == '"' || input[i] == '\''))
            i = dquote_length(input, i, input[i]);
        if(input[i-1] != '\\' && input[i] == '<' && input[i+1] == '<')
        {
            i += 2;
            while (input[i] == ' ' || (input[i] >= 7 && input[i]<= 13))
                i++;
            if (input[i-1] != '\\' && (input[i] == '"' || input[i] == '\''))
            {
                keys[j] = ft_subfirst(input, i + 1, dquote_length(input, i + 1, input[i]) - (i + 2));
                i = dquote_length(input, i, input[i]) - 1;
            }
            else
            {
                keys[j] = ft_subfirst(input, i, key_len(input, i) - i);
                i = key_len(input, i) - 1;
            }
            j++;
        }
        i++;
    }
    keys[j] = NULL;
    return (keys);
}