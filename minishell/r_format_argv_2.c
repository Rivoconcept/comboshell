/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_format_argv_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:26:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/23 15:41:15 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	realloc_new_str(size_t *size, char **new_str)
{
	size_t	j;
	size_t	old_size;
	char	*temp;

	j = 0;
	old_size = *size;
	*size *= 2;
	temp = ft_calloc(*size, sizeof(char));
	if (!temp)
	{
		free(*new_str);
		return (0);
	}
	while (j < old_size)
	{
		temp[j] = (*new_str)[j];
		j++;
	}
	free(*new_str);
	*new_str = temp;
	return (1);
}

void	copy_env(size_t i[2], char *arg, char **new_str, t_params *params)
{
	char	*temp;

	temp = NULL;
	put_var_env(arg, (int *)&i[0], &temp, params);
	if (temp != NULL)
	{
		copy_var_env(temp, *new_str, (int *)&i[1]);
		if (!is_in_myenvp(temp, params->myenvp))
			free(temp);
	}
}

char	*format_var_env(char *arg, t_params *params)
{
	size_t	i[2];
	char	*new_str;
	size_t	size;

	i[0] = (size_t)-1;
	i[1] = 0;
	size = 1024;
	new_str = ft_calloc(size, sizeof(char));
	if (!new_str)
		return (NULL);
	while (arg[++i[0]] != '\0')
	{
		if (i[1] >= size - 1)
		{
			if (!realloc_new_str(&size, &new_str))
				return (NULL);
		}
		if (arg[i[0]] == '$')
			copy_env(i, arg, &new_str, params);
		else
			new_str[i[1]++] = arg[i[0]];
	}
	new_str[i[1]] = '\0';
	return (new_str);
}

void	format_variable(char **argv, t_params *params)
{
	int		i;
	char	*tmp;

	i = 0;
	while (argv[i] != NULL)
	{
		tmp = format_var_env(argv[i], params);
		if (!tmp)
		{
			while (i-- > 0)
				free(argv[i]);
			return ;
		}
		free(argv[i]);
		argv[i] = tmp;
		i++;
	}
}
