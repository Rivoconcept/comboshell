/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrakoton <rrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 07:33:05 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/22 07:33:05 by rrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_variable_name(char *line, int *index)
{
	int		start;
	char	*var_name;

	start = *index;
	while (line[*index] != '\0' && !ft_is_space(line[*index])
		&& line[*index] != '$')
		(*index)++;
	var_name = ft_substr(line, start, *index - start);
	return (var_name);
}

static char	*get_variable_value(t_params *params, char *var_name)
{
	char	*value;

	value = ft_getenv(params, var_name);
	if (!value)
		value = ft_strjoin("$", var_name);
	return (value);
}

static char	*append_segment(char *new_str, char *segment)
{
	char	*joined;

	joined = ft_strjoin(new_str, segment);
	free(new_str);
	return (joined);
}

static char	*process_segment(char *line, int *i, char **new_str,
		t_params *params)
{
	int		start;
	char	*temp;
	char	*var_name;
	char	*value;

	start = *i;
	while (line[*i] != '$' && line[*i] != '\0')
		(*i)++;
	temp = ft_substr(line, start, *i - start);
	*new_str = append_segment(*new_str, temp);
	free(temp);
	if (line[*i] == '$' && line[++(*i)] != '\0')
	{
		var_name = extract_variable_name(line, i);
		value = get_variable_value(params, var_name);
		free(var_name);
		*new_str = append_segment(*new_str, value);
		free(value);
	}
	return (*new_str);
}

char	*expand_variable_in_input(char *line, t_params *params)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	if (!line || !new_str)
		return (NULL);
	while (line[i] != '\0')
	{
		new_str = process_segment(line, &i, &new_str, params);
	}
	return (new_str);
}
