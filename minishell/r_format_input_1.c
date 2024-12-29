/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/29 08:37:36 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	int		j;
	char	*operators;

	j = 0;
	if (!c)
		return (0);
	operators = "|<>";
	while (operators[j])
	{
		if (c == operators[j])
			return (1);
		j++;
	}
	return (0);
}

int	put_new_size(char *input)
{
	int	i;
	int	new_size;

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
    if (*i > 0 && !is_operator(input[*i - 1]) && input[*i - 1] != ' ')
        new_str[(*j)++] = ' ';
    new_str[(*j)++] = input[*i];
    if (input[*i + 1] != '\0' && !is_operator(input[*i + 1]) 
        && input[*i + 1] != ' ')
    {
        if (input[*i + 1] == input[*i])
        {
            (*i)++;
            new_str[(*j)++] = input[*i];
        }
        if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
            new_str[(*j)++] = ' ';
    }
}
void check_left_quote(char *input, int *j, int *lquote)
{
    while (*j >= 0 && input[*j] != ' ' && input[*j] != '\t')
    {
        if (input[*j] == '\'' || input[*j] == '"')
            (*lquote)++;
        (*j)--;
    }
}
void check_right_quote(char *input, int *k, int *rquote)
{
    while (input[*k] != '\0' && input[*k] != ' ' && input[*k] != '\t')
    {
        if (input[*k] == '\'' || input[*k] == '"')
            (*rquote)++;
        (*k)++;
    }
}


