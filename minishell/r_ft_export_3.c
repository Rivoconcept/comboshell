/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_export_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:40:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/20 19:24:41 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_export_name(t_export *myexport, char *name)
{
	t_export	*current;

	if (!name)
		return (0);
	current = myexport;
	while (current != NULL)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(current->name))
		&& ft_strlen(current->name) == ft_strlen(name))
			return (1);
		current = current->next;
	}
	return (0);
}

int del_export_element(t_export **myexport, char *envp)
{
    t_export *current;
    t_export *previous;

    if (!myexport || !*myexport || !envp)
        return (0);
    current = *myexport;
    previous = NULL;
    while (current)
    {
        if (ft_strlen(current->name) == ft_strlen(envp) && 
            ft_strncmp(current->name, envp, ft_strlen(current->name)) == 0)
        {
            if (previous == NULL)
                *myexport = current->next;
            else
                previous->next = current->next;
            return (free(current->name), free(current->value), free(current), 1);
        }
        previous = current;
        current = current->next;
    }
	return (0);
}

char	*put_export_str(t_export *myexport, char *name)
{
	char		*export;
	char		*temp;
	t_export	*current;

	temp = NULL;
	export = NULL;
	current = myexport;
	while (current != NULL)
	{
		if (!ft_strncmp(current->name, name, ft_strlen(current->name))
			&& ft_strlen(current->name) == ft_strlen(name))
		{
			temp = ft_strjoin(name, "=");
			if (current->value == NULL)
				return (temp);
			export = ft_strjoin(temp, current->value);
			free(temp);
			return (export);
		}
		current = current->next;
	}
	return (NULL);
}

char	*put_export_value(t_export *myexport, char *name)
{
	t_export	*current;

	current = myexport;
	while (current != NULL)
	{
		if (!ft_strcmp(current->name, name) 
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


