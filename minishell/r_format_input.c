/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/22 12:09:57 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_operator(char c)
{
    int j;
	char *operators;

	j = 0;
	operators = "&|<>;";
    while (operators[j])
    {
        if (c == operators[j])
            return (1);
        j++;
    }
    return (0);
}

int put_new_size(char *input)
{
    int i;
    int new_size;

	i = -1;
    if (!input || input[0] == '\0')
    {
        return (0);
    }
	new_size = 0;
    while (input[++i])
    {
        if (is_operator(input[i]))
        {
            if (i > 0 && input[i - 1] != ' ')
                new_size++;
            if (input[i + 1] == input[i])
                i++;

            if (input[i + 1] != ' ' && input[i + 1] != '\0')
                new_size++;
        }
    }
    return (ft_strlen(input) + new_size);
}

void add_spaces(char *new_str, char *input, int *i, int *j)
{
    if (*i > 0 && input[*i - 1] != ' ')
        new_str[(*j)++] = ' ';

    new_str[(*j)++] = input[*i];

    if (input[*i + 1] == input[*i])
    {
        (*i)++;
        new_str[(*j)++] = input[*i];
    }

    if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
        new_str[(*j)++] = ' ';
}

char *format_input(char *input)
{
    int i;
    int j;
    char *new_str;

	i = - 1;
	j = 0;
    if (!input)
        return (NULL);
    new_str = malloc(sizeof(char) * (put_new_size(input) + 1));
    if (!new_str)
        return (NULL);
    while (input[++i])
    {
        if (is_operator(input[i]))
            add_spaces(new_str, input, &i, &j);
        else
            new_str[j++] = input[i];
    }
    new_str[j] = '\0';
    return (new_str);
}
