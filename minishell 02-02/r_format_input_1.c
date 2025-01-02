/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:23:16 by rhanitra          #+#    #+#             */
/*   Updated: 2024/01/02 21:33:09 by rhanitra         ###   ########.fr       */
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

void	check_all_possibility(char *s, int *new_size, int i)
{
	while (s[i])
	{
		if (i > 0 && s[i - 1] != ' ' && s[i - 1] != s[i] \
			&& s[i + 1] != ' ' && s[i + 1] != s[i] \
			&& is_out_quote(s, i, s[i]))
			(*new_size) += 2;
		if (i > 0 && s[i - 1] != ' ' && s[i - 1] != s[i] \
			&& s[i + 1] != s[i] && is_out_quote(s, i, s[i]))
			(*new_size)++;
		if (i > 0 && s[i - 1] != ' ' && s[i - 1] != s[i] \
			&& s[i + 1] == s[i] && s[i + 1] != '\0')
			(*new_size)++;
		if (i > 0 && s[i - 1] == s[i] && s[i + 1] != ' ' \
			&& s[i + 1] != s[i] && is_out_quote(s, i, s[i]))
			(*new_size)++;
		if (i > 0 && s[i + 1] != ' ' && s[i + 1] != s[i])
			(*new_size)++;
		if (i == 0 && s[i + 1] != ' ' && s[i + 1] != s[i] \
			&& is_out_quote(s, i, s[i]))
			(*new_size)++;
		i++;
	}
}

int	put_new_size(char *s)
{
	int	i;
	int	new_size;

	i = 0;
	new_size = 0;
	check_all_possibility(s, &new_size, i);
	return ((int)ft_strlen(s) + new_size);
}
