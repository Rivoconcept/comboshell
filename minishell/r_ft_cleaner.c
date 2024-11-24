/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleaner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:40:14 by rhanitra          #+#    #+#             */
/*   Updated: 2024/11/23 11:20:34 by rhanitra         ###   ########.fr       */
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

    while (command)
    {
        temp = command;
        command = command->next;
        free_array(temp->cmd);
        free(temp);
    }
}

void cleanup_and_exit(t_params *params, char *input, int status)
{
    if (params)
    {
        if (params->myenvp)
        {
            free_list_env(params->myenvp);
        }
        if (params->cmd)
        {
            free_list_cmd(params->cmd);
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
    free(input); 
    exit(status);
}

