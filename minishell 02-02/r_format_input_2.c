/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_input_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 11:04:32 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/02 13:58:19 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_add_spaces_1(char *new_str, char *s, int *i, int *j)
{
	if (*i > 0 && s[*i - 1] != ' ' && s[*i - 1] != s[*i] \
		&& s[*i + 1] != ' ' && s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = ' ';
		return (1);
	}
	if (*i > 0 && s[*i - 1] != ' ' && s[*i - 1] != s[*i] \
		&& s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = s[(*i)++];
		return (1);
	}
	if (*i > 0 && s[*i - 1] != ' ' && s[*i - 1] != s[*i] \
		&& s[*i + 1] == s[*i] && s[*i + 1] != '\0')
	{
		new_str[(*j)++] = ' ';
		new_str[(*j)++] = s[(*i)++];
		return (1);
	}
	return (0);
}

int	handle_add_spaces_2(char *new_str, char *s, int *i, int *j)
{
	if (*i > 0 && s[*i - 1] == s[*i] && s[*i + 1] != ' ' \
		&& s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = ' ';
		return (1);
	}
	if (*i > 0 && s[*i + 1] != ' ' && s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = ' ';
		return (1);
	}
	if (*i == 0 && s[*i + 1] != ' ' && s[*i + 1] != s[*i])
	{
		new_str[(*j)++] = s[(*i)++];
		new_str[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

int	add_spaces(char *new_str, char *s, int *i, int *j)
{
	if (handle_add_spaces_1(new_str, s, i, j))
		return (1);
	if (handle_add_spaces_2(new_str, s, i, j))
		return (1);
	return (0);
}
