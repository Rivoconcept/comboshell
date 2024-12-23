/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_init_list_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhanitra <rhanitra@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:21:09 by rhanitra          #+#    #+#             */
/*   Updated: 2024/12/22 07:56:16 by rhanitra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_params *create_list_params(char **envp)
{
    int     i;
    t_params *params;
    
    i = 0;
    params = malloc(sizeof(t_params));
    if (!params)
        return (perror("malloc"), NULL);
    params->myenvp = NULL;
    params->myexport = NULL;
    params->command = NULL;
    params->envp = NULL;
    params->last_exit_code = 0;
    while (envp[i])
    {
        if (!create_env(&params->myenvp, envp[i]))
            return (cleanup_and_exit(params, 1), NULL);
        if (!create_export(&params->myexport, envp[i]))
            return (cleanup_and_exit(params, 1), NULL);
        i++;
    }
    return (params);
}
