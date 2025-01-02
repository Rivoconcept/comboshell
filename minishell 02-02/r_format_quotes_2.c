/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_quotes_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:11:13 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/01 22:49:23 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
	}
	if (c == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
	}
}

int	in_apostrophe(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (str && str[0] == '\'' && str[i - 1] == '\'');
}

int	in_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (str && str[0] == '"' && str[i - 1] == '"');
}

int	check_unmatched_quotes(char *input)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			single_quote++;
		if (input[i] == '"')
			double_quote++;
		i++;
	}
	if (single_quote % 2)
	{
		return (1);
	}
	else if (double_quote % 2)
	{
		return (1);
	}
	return (0);
}
