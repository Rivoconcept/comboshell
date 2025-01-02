/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_env_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:40:01 by rhanitra          #+#    #+#             */
/*   Updated: 2025/01/01 12:47:58 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_alloc_list_env(char **temp, t_env **new_env)
{
	if (!new_env || !*new_env)
	{
		perror("malloc");
		free_array(temp);
		return (1);
	}
	(*new_env)->name = ft_strdup(temp[0]);
	if (!(*new_env)->name)
	{
		free(*new_env);
		free_array(temp);
		return (1);
	}
	return (0);
}

int	alloc_list_env(char **temp, t_env **new_env)
{
	if (check_error_alloc_list_env(temp, new_env) != 0)
		return (1);
	if (temp[1])
	{
		(*new_env)->value = ft_strdup(temp[1]);
		if (!(*new_env)->value)
		{
			free((*new_env)->name);
			free(*new_env);
			free_array(temp);
			return (1);
		}
	}
	else
	{
		(*new_env)->value = ft_strdup("");
		if (!(*new_env)->value)
		{
			free((*new_env)->name);
			free(*new_env);
			free_array(temp);
			return (1);
		}
	}
	return (0);
}

t_env	*create_new_list_env(char *envp)
{
	t_env	*new_env;
	char	**temp;

	temp = ft_split(envp, '=');
	if (!envp || !temp || !temp[0])
	{
		free_array(temp);
		return (NULL);
	}
	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		free_array(temp);
		return (NULL);
	}
	if (alloc_list_env(temp, &new_env) != 0)
	{
		free(new_env);
		free_array(temp);
		return (NULL);
	}
	new_env->next = NULL;
	free_array(temp);
	return (new_env);
}

int	create_env(t_env **myenvp, char *envp)
{
	t_env	*current;
	t_env	*new_env;

	if (!myenvp || !envp)
		return (0);
	new_env = create_new_list_env(envp);
	if (!new_env)
		return (0);
	if (*myenvp == NULL)
		*myenvp = new_env;
	else
	{
		current = *myenvp;
		while (current->next != NULL)
			current = current->next;
		current->next = new_env;
	}
	return (1);
}

char	*put_env_val(t_env *myenv, char *name)
{
	t_env	*current;

	current = myenv;
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
