/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/28 20:19:14 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c, char *operators)
{
	int		j;

	j = 0;
	while (operators[j])
	{
		if (c == operators[j])
			return (1);
		j++;
	}
	return (0);
}

int	put_new_size(char *input, char *operators)
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
		if (is_operator(input[i], operators))
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

void	add_spaces(char *new_str, char *input, int *i, int *j)
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
int check_pipe_out_quote(char *input, int i, char c)
{
    int j;
    int k;
    int quote;

    quote = 0;
    if (input[i] == c)
    {
        j = i - 1;
        k = i + 1; 
        while (j >= 0 && input[j] != ' ' && input[j] != '\t')
        {
            if (input[j] == '\'' || input[j] == '"')
                quote++;
            j--;
        }
        while (input[k] != '\0' && input[k] != ' ' && input[k] != '\t')
        {
            if (input[k] == '\'' || input[k] == '"')
                quote++;
            k++;
        }
        if (quote > 1) 
            return (0);
    }
    return (1);
}
int check_echo(char *s, int *i, char *new_str, int *j)
{
    if (!s || *i < 0)
        return (0);

    if (s[*i] == 'e' && s[*i + 1] == 'c' 
        && s[*i + 2] == 'h' && s[*i + 3] == 'o')
    {
        new_str[(*j)++] = s[(*i)++];
        new_str[(*j)++] = s[(*i)++];
        new_str[(*j)++] = s[(*i)++];
        new_str[(*j)++] = s[(*i)++];
        while (s[*i] != '\0')
        {
			if (s[*i] ==  '|')
			{
				if (!check_pipe_out_quote(s, *i, '|'))
					(*i)++;
				else if (check_pipe_out_quote(s, *i, '|'))
					break;
			}
            new_str[(*j)++] = s[(*i)++];
        }
        return (1);
    }
    return (0);
}
char *format_input(char *input, char *operators)
{
    int i;
    int j;
    char *new_str;

    i = 0;
	j = 0;
	if (!input)
        return (NULL);
    new_str = malloc(sizeof(char) * (put_new_size(input, operators) + 1));
    if (!new_str)
        return (NULL);
		printf("%c\n", input[17]);
		printf("%d\n", check_pipe_out_quote(input, 16, '|'));
    while (input[i])
    {

        if (check_echo(input, &i, new_str, &j))
            continue ;
        if (is_operator(input[i], operators))
            add_spaces(new_str, input, &i, &j);
        else
            new_str[j++] = input[i];
        i++;
    }
    new_str[j] = '\0';
    return (new_str);
}


