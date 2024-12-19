/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_ft_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:14 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/17 22:12:59 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list_env(t_env *myenv)
{
    t_env *temp;

    while (myenv)
    {
        temp = myenv;
        myenv = myenv->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

void free_list_cmd(t_cmd *command)
{
    t_cmd *temp;

    if (command == NULL)
        return ;
    while (command != NULL)
    {
        temp = command->next;
        free_array(command->cmd);
        if (command)
            free(command);
        command = temp;
    }
}

void cleanup_and_exit(t_params *params, int status)
{
    if (params)
    {
        if (params->myenvp)
        {
            free_list_env(params->myenvp);
        }
        if (params->envp)
        {
            free_array(params->envp);
        }
        if (params->var_temp)
        {
            free(params->var_temp);
            params->var_temp = NULL;
        }
        free(params);
    }
    exit(status);
}

