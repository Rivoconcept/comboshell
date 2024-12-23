/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:14 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/24 17:11:11 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	if (arr)
		free(arr);
	arr = NULL;
}

void	free_list_env(t_env *myenv)
{
	t_env	*temp;

	while (myenv)
	{
		temp = myenv;
		myenv = myenv->next;
		free(temp->name);
		temp->name = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
	}
}

void	free_list_export(t_export *myexp)
{
	t_export	*temp;

	while (myexp)
	{
		temp = myexp;
		myexp = myexp->next;
		free(temp->name);
		temp->name = NULL;
		free(temp->value);
		temp->value = NULL;
		free(temp);
	}
}

void	free_list_cmd(t_cmd *command)
{
	t_cmd	*temp;

	if (command == NULL)
		return ;
	while (command != NULL)
	{
		temp = command->next;
		if (command->less)
			free(command->less);
		command->less = NULL;
		if (command->dgreat)
			free(command->dgreat);
		command->dgreat = NULL;
		if (command->great)
			free(command->great);
		command->great = NULL;
		free_array(command->cmd);
		command->cmd = NULL;
		if (command)
			free(command);
		command = temp;
	}
}

void	cleanup_and_exit(t_params *params, int status)
{
	if (params)
	{
		if (params->myenvp)
			free_list_env(params->myenvp);
		if (params->myexport)
			free_list_export(params->myexport);
		if (params->envp)
			free_array(params->envp);
		free(params);
	}
	exit(status);
}
