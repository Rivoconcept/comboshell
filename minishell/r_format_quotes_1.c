/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_quotes_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:02:23 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:50:35 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echap_quote(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote) && !(*in_single_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (1);
	}
	if (c == '\'' && !(*in_double_quote) && *in_single_quote)
	{
		*in_single_quote = !(*in_single_quote);
		return (1);
	}
	if (c == '"' && !(*in_single_quote) && !(*in_double_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (1);
	}
	if (c == '"' && !(*in_single_quote) && *in_double_quote)
	{
		*in_double_quote = !(*in_double_quote);
		return (1);
	}
	return (0);
}

char	*format_quotes(char *command)
{
	int		i[4];
	char	*new_path;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	if (!command)
		return (NULL);
	new_path = (char *)malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!new_path)
		return (NULL);
	while (command[i[0]] != '\0')
	{
		if (echap_quote(command[i[0]], &i[2], &i[3]))
		{
			i[0]++;
			continue ;
		}
		new_path[i[1]++] = command[i[0]++];
	}
	new_path[i[1]] = '\0';
	return (new_path);
}

int	var_in_apostrophe(char *input, int i)
{
	int	nbr;
	int	j;

	nbr = 0;
	if (input[i] == '$')
	{
		j = 0;
		nbr = 0;
		while (j < i)
		{
			if (input[j] == '\'')
				nbr++;
			j++;
		}
		if (nbr % 2 != 0)
			return (1);
	}
	return (0);
}

void	copy_var_env(char *env, char *new_str, int *index)
{
	int	i;

	i = 0;
	while (env[i] != '\0')
	{
		new_str[*index] = env[i];
		(*index)++;
		i++;
	}
}

void	del_quotes(char **argv)
{
	int		i;
	char	*temp;

	i = 0;
	while (argv[i] != NULL)
	{
		if (!argv[i])
		{
			i++;
			continue ;
		}
		temp = format_quotes(argv[i]);
		free(argv[i]);
		argv[i] = temp;
		i++;
	}
}
