/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 23:20:05 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_out_quote(char *input, int i, char c)
{
	int	j;
	int	k;
	int	lquote;
	int	rquote;

	lquote = 0;
	rquote = 0;
	if (input[i] == c && is_operator(c))
	{
		j = i - 1;
		k = i + 1;
		check_left_quote(input, &j, &lquote);
		check_right_quote(input, &k, &rquote);
		if (lquote == 0 || rquote == 0)
			return (1);
		if ((lquote % 2 == 0) && (rquote % 2 == 0))
			return (1);
	}
	return (0);
}

int	check_echo(char *s, int *i, char *new_str, int *j)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	if (!s || *i < 0)
		return (0);
	if (s[*i] == 'e' && s[*i + 1] == 'c' && s[*i + 2] == 'h' && s[*i + 3] == 'o')
	{
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = s[(*i)++];	
		while (s[*i] != '\0' && (squote || dquote || !is_operator(s[*i])))
		{
			handle_quote(s[*i], &squote, &dquote);
			new_str[(*j)++] = s[(*i)++];
		}
		return (1);
	}
	return (0);
}

int	escape_exclamation(char *input, int *i)
{
	if (input[*i] == '!' && (*i == 0 || input[*i - 1] == ' ') \
		&& (input[*i + 1] == '\0' || input[*i + 1] == ' '))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	escape_in_quote(char *input, int *i)
{
	if (is_operator(input[*i]) && is_out_quote(input, *i, input[*i]))
	{
		(*i)++;
		return (1);
	}
	return (0);
}

/*char	*format_input(char *input)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!input)
		return (NULL);
	new_str = malloc(sizeof(char) * (put_new_size(input) + 1));
	if (!new_str)
		return (NULL);
	while (input[i])
	{
		if (escape_exclamation(input, &i))
			continue ;
		if (check_echo(input, &i, new_str, &j))
			continue ;
		if (is_out_quote(input, i, input[i]) \
			&& add_spaces(new_str, input, &i, &j))
			continue ;
		new_str[j++] = input[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}*/

char	*format_input(char *input)
{
	int		i[4];
	char	*new_str;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	if (!input)
		return (NULL);
	new_str = malloc(sizeof(char) * (put_new_size(input) + 1));
	if (!new_str)
		return (NULL);
	while (input[i[0]] != '\0')
	{
		handle_quote(input[i[0]], &i[2], &i[3]);
		if (!i[2] && !i[3] && escape_exclamation(input, &i[0]))
			continue ;
		if (!i[2] && !i[3] && check_echo(input, &i[0], new_str, &i[1]))
			continue ;
		if (!i[2] && !i[3] && is_out_quote(input, i[0], input[i[0]]) \
			&& add_spaces(new_str, input, &i[0], &i[1]))
			continue ;
		new_str[i[1]++] = input[i[0]++];
	}
	return (new_str[i[1]] = '\0', new_str);
}

