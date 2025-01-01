/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/01 22:48:13 by rhanitra         ###   ########.fr       */
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
	operators = "|<>;&";
	while (operators[j])
	{
		if (c == operators[j])
			return (1);
		j++;
	}
	return (0);
}

int	put_new_size(char *s)
{
	int	i;
	int	new_size;

	i = -1;
	new_size = 0;
	while (s[++i])
	{
		if (s[i] && is_out_quote(s, i, s[i]))
		{
			if (i > 0 && s[i - 1] != ' ' && s[i - 1] != s[i] \
				&& s[i + 1] != ' ' && s[i + 1] != s[i])
				new_size += 2;
			if (i > 0 && s[i - 1] == s[i] && s[i + 1] != ' ' \
				&& s[i + 1] != s[i])
				new_size++;
			if (i > 0 && s[i - 1] != ' ' && s[i - 1] != s[i] \
				&& s[i + 1] == s[i])
				new_size++;
		}
	}
	return ((int)strlen(s) + new_size);
}

int	add_spaces(char *new_str, char *s, int *i, int *j)
{
	if (*i > 0 && s[*i - 1] != ' ' && s[*i - 1] != s[*i] \
		&& s[*i + 1] != ' ' && s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = ' ';
		return (1);
	}
	if (*i > 0 && s[*i - 1] == s[*i] && s[*i + 1] != ' ' \
		&& s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = ' ';
		return (1);
	}
	if (*i > 0 && s[*i - 1] != ' ' && s[*i - 1] != s[*i] \
		&& s[*i + 1] == s[*i] && s[*i + 1] == '\0')
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = s[(*i)++];
		return (1);
	}
	return (0);
}

void	check_left_quote(char *input, int *j, int *lquote)
{
	while (*j >= 0 && input[*j] != ' ' && input[*j] != '\t')
	{
		if (input[*j] == '\'' || input[*j] == '"')
			(*lquote)++;
		(*j)--;
	}
}

void	check_right_quote(char *input, int *k, int *rquote)
{
	while (input[*k] != '\0' && input[*k] != ' ' && input[*k] != '\t')
	{
		if (input[*k] == '\'' || input[*k] == '"')
			(*rquote)++;
		(*k)++;
	}
}
