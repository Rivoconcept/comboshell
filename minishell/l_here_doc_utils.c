/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_here_doc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:40:36 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/24 14:53:25 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_heredoc(char **input)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (input[i + 1])
	{
		if (ft_strcmp(input[i], "<<") == 0)
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
		if (ft_strcmp(input[i], "<<") == 0)
			keys[j++] = ft_strdup(input[i + 1]);
		i++;
	}
	keys[j] = NULL;
	return (keys);
}

void	manage_here(t_params *params)
{
	char	**keys;
	t_cmd	*current;
	int		j;

	j = 0;
	current = params->command;
	while (current != NULL)
	{
		keys = here_key(current->cmd);
		process_here(keys, j, params);
		free_array(keys);
		current = current->next;
		j++;
	}
}
