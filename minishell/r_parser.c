/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:39:54 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/13 11:30:05 by rhanitra         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int put_word_len(char *str)
{
    int i;
    int in_single_quote;
    int in_double_quote;

    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    while (str[i] != '\0' && (str[i] != ' '
        || in_single_quote || in_double_quote))
    {
        handle_quotes(str[i], &in_single_quote, &in_double_quote);
        i++;
    }
    return (i);
}

int check_quote(char c, char *str, int *i)
{
    if (str[*i] == c)
    {
        (*i)++;
        while (str[*i] != c && str[*i] != '\0')
            (*i)++;
        if (str[*i] == c && str[*i - 1] !=  c)
        {
            (*i)++;
            return (1);
        }
    }
    return (0);
}

int word_count(char *str)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if (check_quote('\'', str, &i) || check_quote('"', str, &i))
            j++;
        else if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
        {
            j++; 
            while (str[i] != ' ' && str[i] != '\0')
                i++;
        }
        else
            i++;
    }
    return (j);
}


char *split_word(char *str, int index)
{
    int i = 0;
    char *temp;
    int in_single_quote;
    int in_double_quote;

    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    temp = (char *)malloc(sizeof(char) * (put_word_len(&str[index]) + 1));
    if (!temp)
        return (NULL);
    while (str[index] != '\0' && (str[index] != ' '
        || in_single_quote || in_double_quote))
    {
        handle_quotes(str[index], &in_single_quote, &in_double_quote);
        temp[i++] = str[index++];
    }
    temp[i] = '\0';
    return (temp);
}


char **parse_command(char const *input)
{
    int i;
    int j;
    char **split;

    if (!input)
        return (NULL);
    i = 0;
    j = 0;
    split = (char **)malloc(sizeof(char *) * (word_count((char *)input) + 2));
    if (!split)
        return (NULL);
    while (input[i] != '\0')
    {
        if (input[i] != ' ')
        {
            split[j++] = split_word((char *)input, i);
            i += put_word_len((char *)input + i);
        }
        else
            i++;
    }
    split[j] = NULL;
    return (split);
}
