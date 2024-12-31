/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_env_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:31:53 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:50:02 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env_element(t_env **myenv, const char *name)
{
	t_env	*current;
	t_env	*previous;

	if (!myenv || !(*myenv) || !name)
		return ;
	current = *myenv;
	previous = NULL;
	while (current)
	{
		if (current && !ft_strncmp(current->name, name,
				ft_strlen(current->name)) && current->name
			&& ft_strlen(current->name) == ft_strlen(name))
		{
			if (previous == NULL)
				*myenv = current->next;
			else
				previous->next = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

char	*ft_getenv(t_params *params, char *name)
{
	t_env	*current;

	if (!params || !name)
		return (NULL);
	current = params->myenvp;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0
			&& ft_strlen(current->name) == ft_strlen(name))
		{
			if (current->value == NULL)
				return (ft_strdup(""));
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (NULL);
}

int	ft_env(t_params *params)
{
	t_env	*current;

	current = params->myenvp;
	if (current == NULL)
		return (1);
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	return (0);
}
