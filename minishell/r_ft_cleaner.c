/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:14 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/29 15:02:41 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr || arr == NULL)
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
		if (command->less) {
        	free(command->less);
        	command->less = NULL;
		}
		if (command->great) {
			free(command->great);
			command->great = NULL;
		}
		if (command->dgreat) {
			free(command->dgreat);
			command->dgreat = NULL;
		}
		command->here = 0;
		command->rank_here = 0;
		command->flag_less = 0;
		command->rank_less = 0;
		command->rank_great = 0;
		command->rank_dgreat = 0;
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
		if (params->pid_tab)
			free(params->pid_tab);
		if (params->parsed)
		{
			free_array(params->parsed);
			params->parsed = NULL;
		}
		if (params->command)
			free_list_cmd(params->command);
		free(params);
	}
	exit(status);
}
