/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:45:23 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:49:29 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(char c, int *squote, int *dquote)
{
	if (c == '\'' && !(*dquote))
		*squote = !(*squote);
	if (c == '"' && !(*squote))
		*dquote = !(*dquote);
}

int	word_len(char *str)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	while (str[i] != '\0' && (str[i] != ' ' || squote || dquote))
	{
		handle_quote(str[i], &squote, &dquote);
		i++;
	}
	return (i);
}

int	word_count(char *str)
{
	int	i;
	int	count;
	int	squote;
	int	dquote;

	i = 0;
	count = 0;
	squote = 0;
	dquote = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
		{
			count++;
			while (str[i] != '\0' && (str[i] != ' ' || squote || dquote))
			{
				handle_quote(str[i], &squote, &dquote);
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

char	*split_word(char *str, int index)
{
	int		i;
	char	*temp;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	temp = (char *)malloc(sizeof(char) * (word_len(&str[index]) + 1));
	if (!temp)
		return (NULL);
	while (str[index] != '\0' && (str[index] != ' ' || in_single_quote
			|| in_double_quote))
	{
		handle_quote(str[index], &in_single_quote, &in_double_quote);
		temp[i++] = str[index++];
	}
	temp[i] = '\0';
	return (temp);
}

char	**parse_command(char const *input)
{
	int		i;
	int		j;
	char	**split;

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
			i += word_len((char *)input + i);
		}
		else
			i++;
	}
	split[j] = NULL;
	return (split);
}
