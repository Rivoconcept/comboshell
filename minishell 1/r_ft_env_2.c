/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_env_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:40:01 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/31 17:54:48 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var_env(t_env *myenv, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		create_env(&myenv, envp[i]);
		i++;
	}
}

int	count_list_env(t_params *params)
{
	int		i;
	t_env	*current;

	i = 0;
	current = params->myenvp;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

int	join_var_env(t_env **current, char ***myenvp, int *i)
{
	char	*temp;

	temp = ft_strjoin((*current)->name, "=");
	if (!temp)
	{
		free_array(*myenvp);
		return (1);
	}
	(*myenvp)[*i] = ft_strjoin(temp, (*current)->value);
	free(temp);
	if (!(*myenvp)[*i])
	{
		free_array(*myenvp);
		return (1);
	}
	(*i)++;
	return (0);
}

char	**put_envp(t_params *params)
{
	int		i;
	t_env	*current;
	char	**myenvp;
	int		count;

	i = 0;
	count = count_list_env(params);
	myenvp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!myenvp)
		return (NULL);
	current = params->myenvp;
	while (current != NULL)
	{
		if (join_var_env(&current, &myenvp, &i))
		{
			free_array(myenvp);
			return (NULL);
		}
		current = current->next;
	}
	myenvp[i] = NULL;
	return (myenvp);
}
