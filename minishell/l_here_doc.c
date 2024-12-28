/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_here_doc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:41:20 by rrakoton          #+#    #+#             */
/*   Updated: 2024/12/28 11:56:43 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_quotes(char **key)
{
	int		quote;
	char	*temp;

	quote = 0;
	if (ft_memchr(*key, '"', ft_strlen(*key) + 1) || ft_memchr(*key, '\'',
			ft_strlen(*key) + 1))
		quote = 1;
	if (ft_strcmp(*key, "\"\"") != 0 || ft_strcmp(*key, "''") != 0)
	{
		temp = format_quotes(*key);
		free(*key);
		*key = ft_strdup(temp);
		free(temp);
	}
	return (quote);
}
/*void format_keys(char *str)
{
	char    *temp;

	if (!str)
		return ;
	temp = format_input(str, "<> ");
	free(str);
	str = temp;
}*/

int	process_here(char **keys, int j, t_params *params)
{
	int			i;
	char		*here_content;
	t_here_data	here_data;

	here_content = NULL;
	here_data.j = j;
	i = 0;
	while (keys[i])
	{
		here_data.quote = process_quotes(&keys[i]);
		if(handle_here(keys[i], &here_content, &here_data, params)){
			if (here_content)
			{
				free(here_content);
				here_content = NULL;
			}
			return (1);
		}
		if (here_content)
		{
			free(here_content);
			here_content = NULL;
		}
		i++;
	}
	return (0);
}
