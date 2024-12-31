/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_here_doc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:40:36 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/31 13:59:36 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char_valid(const char *input)
{
	size_t	len;
	size_t	i;

	i = 0;
	if (input == NULL || ft_strlen(input) == 0)
		return (0);
	len = ft_strlen(input);
	if ((input[0] == '"' && input[len - 1] == '"') || (input[0] == '\''
			&& input[len - 1] == '\''))
		return (1);
	while (i < ft_strlen(input))
	{
		if (!ft_isalnum(input[i]) && input[i] != '"' && input[i] != '\''
			&& input[i] != '_' && input[i] != '$' && input[i] != '.'
			&& input[i] != '-')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

static int	count_heredoc(char **input)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (input[i + 1])
	{
		if (ft_strcmp(input[i], "<<") == 0 && input[i + 1])
			nbr++;
		i++;
	}
	return (nbr);
}

static char	**here_key(char **input)
{
	int		i;
	int		j;
	char	**keys;

	i = 0;
	j = 0;
	keys = (char **)malloc(sizeof(char *) * (count_heredoc(input) + 1));
	while (input[i + 1])
	{
		if (ft_strcmp(input[i], "<<") == 0 && input[i + 1])
			keys[j++] = ft_strdup(input[i + 1]);
		i++;
	}
	keys[j] = NULL;
	return (keys);
}

int	manage_here(t_params *params)
{
	int		j;
	t_cmd	*current;
	char	**keys;

	j = 0;
	current = params->command;
	while (current != NULL)
	{
		keys = here_key(current->cmd);
		if (process_here(keys, j, params))
		{
			free_array(keys);
			return (1);
		}
		free_array(keys);
		current = current->next;
		j++;
	}
	return (0);
}
